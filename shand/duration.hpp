#ifndef SHAND_DURATION_INCLUDE
#define SHAND_DURATION_INCLUDE

// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <chrono>

namespace shand {

template <class Rep>
using nanoseconds_t = std::chrono::duration<Rep, std::nano>;
using nanoseconds_f = nanoseconds_t<float>;
using nanoseconds_d = nanoseconds_t<double>;
using nanoseconds_ld = nanoseconds_t<long double>;

template <class Rep>
using microseconds_t = std::chrono::duration<Rep, std::micro>;
using microseconds_f = microseconds_t<float>;
using microseconds_d = microseconds_t<double>;
using microseconds_ld = microseconds_t<long double>;

template <class Rep>
using milliseconds_t = std::chrono::duration<Rep, std::milli>;
using milliseconds_f = milliseconds_t<float>;
using milliseconds_d = milliseconds_t<double>;
using milliseconds_ld = milliseconds_t<long double>;

template <class Rep>
using seconds_t = std::chrono::duration<Rep>;
using seconds_f = seconds_t<float>;
using seconds_d = seconds_t<double>;
using seconds_ld = seconds_t<long double>;

template <class Rep>
using minutes_t =  std::chrono::duration<Rep, std::ratio<60>>;
using minutes_f = minutes_t<float>;
using minutes_d = minutes_t<double>;
using minutes_ld = minutes_t<long double>;

template <class Rep>
using hours_t = std::chrono::duration<Rep, std::ratio<3600>>;
using hours_f = hours_t<float>;
using hours_d = hours_t<double>;
using hours_ld = hours_t<long double>;

} // namespace shand

#endif // SHAND_DURATION_INCLUDE

