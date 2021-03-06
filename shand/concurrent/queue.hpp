#ifndef SHAND_CONCURRENT_QUEUE_INCLUDE
#define SHAND_CONCURRENT_QUEUE_INCLUDE

// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <deque>
#include <utility>
#include <mutex>
#include <shared_mutex>
#include <boost/optional.hpp>
 
namespace shand {
 
template <class T>
class concurrent_queue {
    // If this requirement is true, optional(T&&) also nothrow (by document 1.57.0)
    static_assert(
        std::is_nothrow_move_constructible<T>::value,
        "Type T must be nothrow move constructible");
 
    std::deque<T> que_;
    mutable std::shared_timed_mutex mutex_;
public:
    concurrent_queue() {}
 
    concurrent_queue(const concurrent_queue&) = delete;
    concurrent_queue& operator=(const concurrent_queue&) = delete;
 
    // write access
    void push(const T& x)
    {
        std::lock_guard<std::shared_timed_mutex> lock(mutex_);
        que_.push_back(x);
    }
 
    void push(T&& x)
    {
        std::lock_guard<std::shared_timed_mutex> lock(mutex_);
        que_.push_back(std::move(x));
    }
 
    boost::optional<T> pop() noexcept
    {
        std::lock_guard<std::shared_timed_mutex> lock(mutex_);
        if (que_.empty())
            return boost::none;
 
        T front = std::move(que_.front());
        que_.pop_front();
        return front;
    }
 
    void clear()
    {
        std::lock_guard<std::shared_timed_mutex> lock(mutex_);
        que_.clear();
    }
 
    // read access
    std::size_t size() const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return que_.size();
    }
 
    bool empty() const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return que_.empty();
    }
};
 
} // namespace shand

#endif // SHAND_CONCURRENT_QUEUE_INCLUDE

