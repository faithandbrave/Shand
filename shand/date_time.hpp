#ifndef SHAND_DATE_TIME_INCLUDE
#define SHAND_DATE_TIME_INCLUDE

// Shand Date Time Library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cstddef>
#include <ctime>
#include <stdexcept>
#include <map>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/format.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/utility/enable_if.hpp>

namespace shand {

template <int>
class primitive {
    std::size_t value_;
public:
    primitive() : value_(0) {}
    explicit primitive(std::size_t value) : value_(value) {}
    std::size_t value() const { return value_; }
};

typedef primitive<0> year;
typedef primitive<1> month;
typedef primitive<2> day;
typedef primitive<3> hour;
typedef primitive<4> minute;
typedef primitive<5> second;

#ifdef SHAND_DATE_TIME_CUSTOM_NOW_TIME
    std::time_t now_time_t();
#else
    inline std::time_t now_time_t()
    {
        std::time_t t;
        std::time(&t);
        return t;
    }
#endif

template <int I, int J>
inline boost::fusion::vector<primitive<I>, primitive<J> >
    operator&(const primitive<I>& a, const primitive<J>& b)
{
    return boost::fusion::make_vector(a, b);
}

template <class Seq, int I>
inline typename boost::lazy_enable_if<
                    boost::fusion::traits::is_sequence<Seq>,
                    boost::fusion::result_of::push_back<const Seq, primitive<I> > >::type
    operator&(const Seq& a, const primitive<I>& b)
{
    return boost::fusion::push_back(a, b);
}

namespace detail {

class primitive_assigner {
    std::tm* st_;
public:
    primitive_assigner(std::tm* st) : st_(st) {}

    void operator()(const year& x) const    { st_->tm_year = x.value() - 1900; }
    void operator()(const month& x) const   { st_->tm_mon  = x.value() - 1; }
    void operator()(const day& x) const     { st_->tm_mday = x.value(); }
    void operator()(const hour& x) const    { st_->tm_hour = x.value(); }
    void operator()(const minute& x) const  { st_->tm_min  = x.value(); }
    void operator()(const second& x) const  { st_->tm_sec  = x.value(); }
};

class primitive_extractor {
    const std::tm& st_;
public:
    primitive_extractor(const std::tm& st) : st_(st) {}

    void operator()(year& x) const      { x = year(st_.tm_year + 1900); }
    void operator()(month& x) const     { x = month(st_.tm_mon + 1); }
    void operator()(day& x) const       { x = day(st_.tm_mday); }
    void operator()(hour& x) const      { x = hour(st_.tm_hour); }
    void operator()(minute& x) const    { x = minute(st_.tm_min); }
    void operator()(second& x) const    { x = second(st_.tm_sec); }

    // skip other
    template <class T>
    void operator()(T&) const {}
};

inline std::tm std_localtime(std::time_t time)
{
#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
    std::tm st;
    const errno_t err = localtime_s(&st, &time);
    if (err != 0) {
        const std::string what = (boost::format("could not convert time to tm. err:%1%") % err).str();
        boost::throw_exception(std::runtime_error(what));
    }

    return st;
#else
    std::tm* st = std::localtime(&time);
    if (!st) {
        boost::throw_exception(std::runtime_error("could not convert time to tm."));
    }

    return *st;
#endif
}

} // namespace detail

class date_time {
    std::time_t time_;

    template <class F>
    date_time& assign_time(F f)
    {
        std::tm st = detail::std_localtime(time_);

        f(&st);

        time_ = std::mktime(&st);
        return *this;
    }

    template <class F>
    static date_time calc_time(const date_time& d, F f)
    {
        std::tm st = detail::std_localtime(d.time_);

        f(&st);

        return date_time(std::mktime(&st));
    }

public:
    date_time() : time_(0) {}
    explicit date_time(std::time_t t) : time_(t) {}

    template <class Seq>
    date_time(const Seq& seq,
        typename boost::enable_if<boost::fusion::traits::is_sequence<Seq> >::type* = 0)
    {
        std::tm st = detail::std_localtime(now_time_t());

        boost::fusion::for_each(seq, detail::primitive_assigner(&st));

        time_ = std::mktime(&st);
    }

    std::string format(const std::string& fmt) const
    {
        BOOST_ASSERT(time_ >= 0);

        std::tm st = detail::std_localtime(time_);

        const std::map<std::string, std::string> rep = boost::assign::list_of
            (std::make_pair("%Y", (boost::format("%04d") % (1900 + st.tm_year)).str()))
            (std::make_pair("%m", (boost::format("%02d") % (1 + st.tm_mon)).str()))
            (std::make_pair("%d", (boost::format("%02d") % st.tm_mday).str()))
            (std::make_pair("%H", (boost::format("%02d") % st.tm_hour).str()))
            (std::make_pair("%M", (boost::format("%02d") % st.tm_min).str()))
            (std::make_pair("%S", (boost::format("%02d") % st.tm_sec).str()))
        ;

        using namespace boost::xpressive;

        local<std::string const *> pstr;
        const sregex rx = (a1 = rep)[pstr = &a1];

        return regex_replace(fmt, rx, *pstr);
    }

    static date_time now()
    {
        return date_time(now_time_t());
    }

    time_t to_time_t() const { return time_; }

    // assign
    template <class Seq>
    typename boost::enable_if<boost::fusion::traits::is_sequence<Seq>, date_time&>::type
        operator=(const Seq& seq)
    {
        std::tm st = detail::std_localtime(time_);

        boost::fusion::for_each(seq, detail::primitive_assigner(&st));

        time_ = std::mktime(&st);
        return *this;
    }

    date_time& operator=(const year& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_year = x.value() - 1900); }

    date_time& operator=(const month& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_mon = x.value() - 1); }

    date_time& operator=(const day& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_mday = x.value()); }

    date_time& operator=(const hour& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_hour = x.value()); }

    date_time& operator=(const minute& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_min = x.value()); }

    date_time& operator=(const second& x)
        { return assign_time(boost::lambda::_1 ->* &std::tm::tm_sec = x.value()); }

    // add
    friend date_time operator+(const date_time& d, const year& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_year += x.value()); }

    friend date_time operator+(const date_time& d, const month& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_mon += x.value()); }

    friend date_time operator+(const date_time& d, const day& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_mday += x.value()); }

    friend date_time operator+(const date_time& d, const hour& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_hour += x.value()); }

    friend date_time operator+(const date_time& d, const minute& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_min += x.value()); }

    friend date_time operator+(const date_time& d, const second& x)
        { return calc_time(d, boost::lambda::_1 ->* &std::tm::tm_sec += x.value()); }

    // substract
    friend date_time operator-(const date_time& d, const year& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_year -= x.value()); }

    friend date_time operator-(const date_time& d, const month& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_mon -= x.value()); }

    friend date_time operator-(const date_time& d, const day& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_mday -= x.value()); }

    friend date_time operator-(const date_time& d, const hour& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_hour -= x.value()); }

    friend date_time operator-(const date_time& d, const minute& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_min -= x.value()); }

    friend date_time operator-(const date_time& d, const second& x)
        { return date_time::calc_time(d, boost::lambda::_1 ->* &std::tm::tm_sec -= x.value()); }

    template <class ExtractPrimitives>
    ExtractPrimitives extract() const
    {
        BOOST_MPL_ASSERT((boost::fusion::traits::is_sequence<ExtractPrimitives>));

        std::tm st = detail::std_localtime(time_);

        ExtractPrimitives result;
        boost::fusion::for_each(result, detail::primitive_extractor(st));

        return result;
    }

    template <class OutputSequence>
    void extract(OutputSequence& result) const
    {
        BOOST_MPL_ASSERT((boost::fusion::traits::is_sequence<OutputSequence>));

        std::tm st = detail::std_localtime(time_);

        boost::fusion::for_each(result, detail::primitive_extractor(st));
    }
};


inline day diff_day(const date_time& a, const date_time& b)
{
    const std::time_t& at = (std::max)(a.to_time_t(), b.to_time_t());
    const std::time_t& bt = (std::min)(a.to_time_t(), b.to_time_t());
    return day(static_cast<std::size_t>(std::difftime(at, bt) / (60 * 60 * 24)));
}

inline hour diff_hour(const date_time& a, const date_time& b)
{
    const std::time_t& at = (std::max)(a.to_time_t(), b.to_time_t());
    const std::time_t& bt = (std::min)(a.to_time_t(), b.to_time_t());
    return hour(static_cast<std::size_t>(std::difftime(at, bt) / (60 * 60)));
}

inline minute diff_minute(const date_time& a, const date_time& b)
{
    const std::time_t& at = (std::max)(a.to_time_t(), b.to_time_t());
    const std::time_t& bt = (std::min)(a.to_time_t(), b.to_time_t());
    return minute(static_cast<std::size_t>(std::difftime(at, bt) / 60));
}

inline second diff_second(const date_time& a, const date_time& b)
{
    const std::time_t& at = (std::max)(a.to_time_t(), b.to_time_t());
    const std::time_t& bt = (std::min)(a.to_time_t(), b.to_time_t());
    return second(static_cast<std::size_t>(std::difftime(at, bt)));
}

} // namespace shand

#endif // SHAND_DATE_TIME_INCLUDE

