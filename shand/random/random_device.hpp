#ifndef SHAND_RANDOM_DEVICE_INCLUDE
#define SHAND_RANDOM_DEVICE_INCLUDE

// `shand::random_device` is bit specified random_device.
// The class need for `mt19937_64`'s seed.
//
// synopsis is follow:
//
// namespace shand {
//   template <class UIntType>
//   class random_device {
//     using result_type = UIntType;
//
//     explicit random_device(const std::string& token = implementation-defined);
//     result_type operator()();
//
//     template <class Iterator>
//     void generate(Iterator first, Iterator last);
//   };
//
//   using random_device_32 = random_device<std::uint32_t>;
//   using random_device_64 = random_device<std::uint64_t>;
// }
//
// Copyright Akira Takahashi 2014.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Original implementation's license :
// Copyright Jens Maurer 2000
// Copyright Steven Watanabe 2010-2011
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/detail/workaround.hpp>

#include <cstdint>
#include <limits>
#include <stdexcept>

#if defined(BOOST_WINDOWS)
#include <windows.h>
#include <wincrypt.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    // open
#include <unistd.h>   // read, close
#include <errno.h>    // errno
#include <string.h>   // strerror
#endif

namespace shand {

namespace random_device_detail {

#if defined(BOOST_WINDOWS)
    template <class UIntType>
    struct impl {
        impl()
        : impl(MS_DEF_PROV_A) {}

        impl(const std::string& token)
            : provider(token)
        {
            char buffer[80];
            DWORD type;
            DWORD len;

            // Find the type of the provider
            for (DWORD i = 0;; ++i) {
                len = sizeof(buffer);
                if (!CryptEnumProvidersA(i, NULL, 0, &type, buffer, &len)) {
                    error("Could not find provider name");
                }
                if (buffer == provider) {
                    break;
                }
            }

            if (!CryptAcquireContextA(&hProv, NULL, provider.c_str(), type,
                CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
                error("Could not acquire CSP context");
            }
        }

        ~impl() {
            if (!CryptReleaseContext(hProv, 0))
                error("Could not release CSP context");
        }

        impl(const impl&) = delete;
        void operator=(const impl&) = delete;

        UIntType next() {
            UIntType result;

            if (!CryptGenRandom(hProv, sizeof(result),
                static_cast<BYTE*>(static_cast<void*>(&result)))) {
                error("error while reading");
            }

            return result;
        }

    private:
        void error(const std::string & msg) {
            char buf[80];
            DWORD num = FormatMessageA(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                0,
                buf,
                sizeof(buf),
                NULL);

            boost::throw_exception(std::invalid_argument("boost::random_device: " + msg +
                " Cryptopraphic Service Provider " + provider +
                ": " + std::string(&buf[0], &buf[0] + num)));
        }

        const std::string provider;
        HCRYPTPROV hProv;
    };

#else

    template <class UIntType>
    struct impl {
        impl()
        : impl("/dev/urandom") {}

        impl(const std::string& token)
            : path(token)
        {
            fd = open(token.c_str(), O_RDONLY);
            if (fd < 0)
                error("cannot open");
        }

        ~impl() { if (close(fd) < 0) error("could not close"); }

        impl(const impl&) = delete;
        void operator=(const impl&) = delete;

        UIntType next() {
            UIntType result;
            long sz = read(fd, reinterpret_cast<char *>(&result), sizeof(result));
            if (sz == -1)
                error("error while reading");
            else if (sz != sizeof(result)) {
                errno = 0;
                error("EOF while reading");
            }
            return result;
        }

    private:
        void error(const std::string & msg) {
            boost::throw_exception(std::invalid_argument("boost::random_device: " + msg +
                " random-number pseudo-device " + path +
                ": " + strerror(errno)));
        }

        const std::string path;
        int fd;
    };

#endif

} // namespace random_device_detail

// `shand::random_device` is bit specified random_device.
// The class need for `mt19937_64`'s seed.
template <class UIntType>
class random_device {
    random_device_detail::impl<UIntType> impl_;
public:
    using result_type = UIntType;

    random_device() {}

    explicit random_device(const std::string& token)
        : impl_(token) {}

    random_device(const random_device&) = delete;
    void operator=(const random_device&) = delete;

    result_type operator()()
    {
        return impl_.next();
    }

    static result_type (min)() { return (std::numeric_limits<result_type>::min)(); }
    static result_type (max)() { return (std::numeric_limits<result_type>::max)(); }

    template<class Iter>
    void generate(Iter begin, Iter end)
    {
        for (; begin != end; ++begin) {
            *begin = (*this)();
        }
    }
};

// 32bit random_device
using random_device_32 = ::shand::random_device<std::uint32_t>;

// 64bit random_device
using random_device_64 = ::shand::random_device<std::uint64_t>;

} // namespace shand

#endif // SHAND_RANDOM_DEVICE_INCLUDE


