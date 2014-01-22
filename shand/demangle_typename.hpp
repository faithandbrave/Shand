#ifndef SHAND_DEMANGLE_TYPENAME_INCLUDE
#define SHAND_DEMANGLE_TYPENAME_INCLUDE

// demangle std::typeinfo::name()
//
// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/predef.h>
#include <string>

#if BOOST_LIB_STD_GNU || BOOST_LIB_STD_CXX
#include <cxxabi.h>
#include <cstdlib> // std::free
#endif

#include <boost/scope_exit.hpp>

namespace shand {

#if BOOST_LIB_STD_GNU || BOOST_LIB_STD_CXX
    template <class T>
    std::string demangle_typename()
    {
        int status = 0;
        char* demangled = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);

        BOOST_SCOPE_EXIT_TPL(demangled) {
            std::free(demangled);
        } BOOST_SCOPE_EXIT_END

        return std::string(demangled);
    }
#else
    template <class T>
    std::string demangle_typename()
    {
        return typeid(T).name();
    }
#endif

} // namespace shand

#endif // SHAND_DEMANGLE_TYPENAME_INCLUDE

