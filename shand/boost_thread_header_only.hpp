#ifndef HEADER_ONLY_BOOST_THREAD_INCLUDE
#define HEADER_ONLY_BOOST_THREAD_INCLUDE

// This Header is For Boost.Thread header only use.
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_ERROR_CODE_HEADER_ONLY
#endif

#ifndef BOOST_THREAD_NO_LIB
#define BOOST_THREAD_NO_LIB
#endif

#ifndef BOOST_DATE_TIME_NO_LIB
#define BOOST_DATE_TIME_NO_LIB
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_THREAD_HEADER_ONLY_NO_DLL)
	#if defined(BOOST_HAS_DECLSPEC)
		#undef BOOST_HAS_DECLSPEC
	#endif
#endif

#include <boost/thread.hpp>

#if defined(BOOST_THREAD_PLATFORM_WIN32)
    #include <boost/../libs/thread/src/win32/timeconv.inl>
    #include <boost/../libs/thread/src/win32/thread.cpp>
    #include <boost/../libs/thread/src/win32/tss_dll.cpp>
    #include <boost/../libs/thread/src/win32/tss_pe.cpp>
#else
//  #include <boost/../libs/thread/src/pthread/timeconv.inl> // DateTimeé¸ÇËÇ≈çƒíËã`ÉGÉâÅ[Ç…Ç»ÇÈÇÃÇ≈âˆÇµÇ¢
    #include <boost/../libs/thread/src/pthread/once.cpp>
    #include <boost/../libs/thread/src/pthread/thread.cpp>
#endif

namespace boost {
void tss_cleanup_implemented() {}
}

#endif // HEADER_ONLY_BOOST_THREAD_INCLUDE


