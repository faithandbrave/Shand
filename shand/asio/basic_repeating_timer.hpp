#ifndef BOOST_ASIO_REPEATING_TIMER_H_INCLUDED
#define BOOST_ASIO_REPEATING_TIMER_H_INCLUDED

// Developed 2007 by David C. Wyles (http:///www.codegorilla.co.uk)
// released for public consumption under the same 
// licensing policy as the boost library http://www.boost.org/LICENSE_1_0.txt
//
// most people will use the repeating_timer typedef for working with posix time
//
// Is is based on the basic_deadline_timer
//

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/weak_ptr.hpp>

namespace boost
{
namespace asio
{
    // basic repeating timer with start stop semantics.

    template <typename Time,
              typename TimeTraits = boost::asio::time_traits<Time>,
              typename TimerService = boost::asio::deadline_timer_service<Time, TimeTraits> >
    class basic_repeating_timer : public boost::asio::basic_io_object<TimerService>
    {
    public:
        typedef boost::asio::basic_deadline_timer<Time>  timer_type;

        explicit basic_repeating_timer( boost::asio::io_service& io_service )
            : boost::asio::basic_io_object<TimerService>(io_service)
        {
        }

        ~basic_repeating_timer()
        {
            stop();
        }

        template <typename WaitHandler>
        void start( typename timer_type::duration_type const & repeat_interval, WaitHandler handler )
        {
            boost::recursive_mutex::scoped_lock guard(lock_);
            {
                // cleanup code, cancel any existing timer
                handler_.reset();
                if( timer_ )
                {
                    timer_->cancel();
                }
                timer_.reset();
            }            

            // create new handler.
            handler_.reset( new handler_impl<WaitHandler>( handler ) );
            // create new timer
            timer_ = internal_timer::create( this->io_service(), repeat_interval, handler_ );
        }

        void stop()
        {
            boost::recursive_mutex::scoped_lock guard(lock_);
            {
                // cleanup code.
                handler_.reset();
                if( timer_ )
                {
                    timer_->cancel();
                }
                timer_.reset();
            }            
        }

        void cancel() {stop();}

        // changes the interval the next time the timer is fired.
        void change_interval( typename timer_type::duration_type const & repeat_interval )
        {
            boost::recursive_mutex::scoped_lock guard(lock_);
            if( timer_ )
            {
                timer_->change_interval( repeat_interval );
            }
        }

    private:

        boost::recursive_mutex  lock_;
        class internal_timer;
        typedef boost::shared_ptr<internal_timer>   internal_timer_ptr;
        internal_timer_ptr      timer_;

        class handler_base;
        boost::shared_ptr<handler_base> handler_;

        class handler_base
        {
        public:
            virtual ~handler_base() {}
            virtual void handler( boost::system::error_code const & ) = 0;
        };

        template <typename HandlerFunc>
        class handler_impl : public handler_base
        {
        public:
            handler_impl( HandlerFunc func ) : handler_func_(func) {}
            virtual void handler( boost::system::error_code const & result )
            {
                handler_func_(result);
            }
            HandlerFunc handler_func_;
        };

        class internal_timer : public boost::enable_shared_from_this<internal_timer>
        {
        public:
            static internal_timer_ptr create( boost::asio::io_service& io_service,
                                              typename timer_type::duration_type const & repeat_interval, 
                                              boost::shared_ptr<handler_base> const & handler )
            {
                internal_timer_ptr timer( new internal_timer( io_service ) );
                timer->start( repeat_interval, handler );
                return timer;
            }

            void cancel()
            {
                boost::recursive_mutex::scoped_lock guard( lock_ );
                timer_.cancel();
            }

            void change_interval( typename timer_type::duration_type const & repeat_interval )
            {
                boost::recursive_mutex::scoped_lock guard( lock_ );
                interval_ = repeat_interval;
            }

        private:
            timer_type                          timer_;
            boost::weak_ptr<handler_base>       handler_;
            typename timer_type::duration_type  interval_;
            boost::recursive_mutex              lock_;

            internal_timer( boost::asio::io_service& io_service )
                :timer_(io_service)
            {
            }

            void start( typename timer_type::duration_type const & repeat_interval, 
                        boost::shared_ptr<handler_base> const & handler )
            {
                // only EVER called once, via create
                interval_ = repeat_interval;
                handler_ = handler;

                timer_.expires_from_now( interval_ );
                timer_.async_wait( boost::bind( &internal_timer::handle_timeout, this->shared_from_this(), boost::asio::placeholders::error ) );
            }

            void handle_timeout(boost::system::error_code const& error)
            {
                // we lock in the timeout to block the cancel operation until this timeout completes
                boost::recursive_mutex::scoped_lock guard( lock_ );
                {
                    // do the fire.
                    boost::shared_ptr<handler_base> Handler = handler_.lock();
                    if( Handler )
                    {
                        try
                        {
                            Handler->handler(error);
                        }
                        catch( std::exception const & e )
                        {
                            // consume for now, no much else we can do, we don't want to damage the
                            // io_service thread
                            (void)e;
                        }
                    }
                }
                
                if( !error )
                {
                    // check if we need to reschedule.
                    boost::shared_ptr<handler_base> Handler = handler_.lock();
                    if( Handler )
                    {
                        timer_.expires_from_now( interval_ );
                        //m_Timer.expires_at( m_Timer.expires_at() + m_Repeat_Interval );
                        timer_.async_wait( boost::bind( &internal_timer::handle_timeout, this->shared_from_this(), boost::asio::placeholders::error ) );
                    }
                }
            }
        };
    };

    typedef basic_repeating_timer<boost::posix_time::ptime> repeating_timer;
}
}

#endif

