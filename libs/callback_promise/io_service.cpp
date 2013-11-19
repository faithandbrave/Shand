// Copyright Akira Takahashi 2013.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <list>
#include <boost/function.hpp>
#include <shand/callback_promise.hpp>

// Not good sample.
// This case can use `function` instead of `callback_promise`.
class io_service {
    std::list<boost::function<void()>> callback_queue_;
    shand::callback_promise<void> promise_;
public:
    template <class F>
    io_service& post(F f)
    {
        promise_.set_callback(f);
        return *this;
    }

    template <class F>
    io_service& then(F f)
    {
        callback_queue_.push_back(f);
        return *this;
    }

    void run()
    {
        while (!callback_queue_.empty()) {
            promise_.set_value();
            promise_.clear();
            callback_queue_.front()();
            callback_queue_.pop_front();
        }
    }
};

void f1() { std::cout << 0 << std::endl; }
void f2() { std::cout << 1 << std::endl; }
void f3() { std::cout << 2 << std::endl; }

int main()
{
    io_service ios;

    ios.post(f1)
       .then([&] { ios.post(f2); })
       .then([&] { ios.post(f3); })
       .then([]{});

    ios.run();
}
