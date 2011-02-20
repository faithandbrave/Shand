#ifndef FUSION_FLATTEN_INCLUDE
#define FUSION_FLATTEN_INCLUDE

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/join.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <boost/fusion/include/is_sequence.hpp>

namespace result_of
{
    template < typename Begin, typename End, class Enable = void >
    struct flatten_impl
    {
        typedef boost::fusion::single_view< typename 
            boost::fusion::result_of::value_of< Begin >::type 
        > flattenedHeadSequence;

        typedef typename 
            flatten_impl< typename
                boost::fusion::result_of::next< Begin >::type,
                End
            >::type flattenedTailSequence;

        typedef typename boost::fusion::result_of::join< const flattenedHeadSequence, const flattenedTailSequence >::type type;
    };


    template < typename Begin, typename End >
    struct flatten_impl< 
        Begin, 
        End, typename
        boost::enable_if< 
            boost::fusion::traits::is_sequence< typename
                boost::fusion::result_of::value_of< Begin >::type
            >
        >::type 
    >
    {
        typedef typename boost::fusion::result_of::value_of< Begin >::type headSequence;
        typedef typename 
            flatten_impl< typename
                boost::fusion::result_of::begin< headSequence >::type, typename
                boost::fusion::result_of::end< headSequence >::type 
            >::type flattenedHeadSequence;

        typedef typename 
            flatten_impl< typename
                boost::fusion::result_of::next< Begin >::type,
                End
            >::type flattenedTailSequence;

        typedef typename boost::fusion::result_of::join< const flattenedHeadSequence, const flattenedTailSequence >::type type;
    };


    template < typename End, typename Enable >
    struct flatten_impl< End, End, Enable >
    {
        typedef boost::fusion::vector< > type;
    };


    template < typename Sequence >
    struct flatten
    {
        typedef typename 
            flatten_impl< typename 
                boost::fusion::result_of::begin< Sequence >::type, typename 
                boost::fusion::result_of::end< Sequence >::type 
            >::type type;
    };    
}


template < typename Begin, typename End >
typename result_of::flatten_impl< Begin, End >::type 
flatten_impl( 
    const Begin & begin, 
    const End & end, typename 
    boost::disable_if<
        boost::fusion::traits::is_sequence< typename
            boost::fusion::result_of::value_of< Begin >::type
        >
    >::type * dummy = 0 )
{
    typedef result_of::flatten_impl< Begin, End > traits;
    typedef typename traits::flattenedHeadSequence headSequence;
    typedef typename traits::flattenedTailSequence tailSequence;

    return boost::fusion::join( 
        headSequence( boost::fusion::deref( begin ) ),
        flatten_impl( boost::fusion::next( begin ), end ) );
}


template < typename Begin, typename End >
typename result_of::flatten_impl< Begin, End >::type 
flatten_impl( 
    const Begin & begin, 
    const End & end, typename 
    boost::enable_if<
        boost::fusion::traits::is_sequence< typename
            boost::fusion::result_of::value_of< Begin >::type
        >
    >::type * dummy = 0 )
{
    typedef result_of::flatten_impl< Begin, End > traits;
    typedef typename traits::flattenedHeadSequence headSequence;
    typedef typename traits::flattenedTailSequence tailSequence;

    typedef typename traits::headSequence headType;

    const headType & head = boost::fusion::deref( begin );

    return boost::fusion::join(
        flatten_impl( boost::fusion::begin( head ), boost::fusion::end( head ) ),
        flatten_impl( boost::fusion::next( begin ), end ) );
}


template < typename End >
typename result_of::flatten_impl< End, End >::type
flatten_impl( const End &, const End &)
{
    return boost::fusion::make_vector( );
}


template < typename Sequence >
typename result_of::flatten< Sequence >::type 
flatten( const Sequence & seq )
{
    return flatten_impl( boost::fusion::begin( seq ), boost::fusion::end( seq ) );
}

#endif // FUSION_FLATTEN_INCLUDE

