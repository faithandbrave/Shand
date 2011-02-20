#ifndef SHAND_FUSION_COPY_INCLUDE
#define SHAND_FUSION_COPY_INCLUDE

// Shand, Boost.Fusion extended library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>

namespace shand { namespace fusion {

template <class IIteratorFirst, class IIteratorLast, class OIteratorFirst>
void copy_impl(IIteratorFirst ifirst, IIteratorLast ilast, OIteratorFirst result, boost::mpl::true_)
{
}

template <class IIteratorFirst, class IIteratorLast, class OIteratorFirst>
void copy_impl(IIteratorFirst ifirst, IIteratorLast ilast, OIteratorFirst result, boost::mpl::false_)
{
    namespace fusion = boost::fusion;

    *result = *ifirst;

    copy_impl(fusion::next(ifirst), ilast, fusion::next(result),
                fusion::result_of::equal_to<
                    typename fusion::result_of::next<IIteratorFirst>::type,
                    IIteratorLast
                >());
}

template <class InputSequence, class OutputSequence>
void copy(const InputSequence& input, OutputSequence& output)
{
    namespace fusion = boost::fusion;

    BOOST_STATIC_ASSERT(fusion::result_of::size<InputSequence>::value ==
                        fusion::result_of::size<OutputSequence>::value);

    copy_impl(fusion::begin(input), fusion::end(input), fusion::begin(output),
                fusion::result_of::equal_to<
                    typename fusion::result_of::begin<InputSequence>::type,
                    typename fusion::result_of::end<InputSequence>::type
                >());
}

}} // namespace shand::fusion

#endif // SHAND_FUSION_COPY_INCLUDE

