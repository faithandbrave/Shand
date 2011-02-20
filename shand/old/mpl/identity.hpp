#ifndef SHAND_MPL_IDENTITY_INCLUDE
#define SHAND_MPL_IDENTITY_INCLUDE

namespace shand { namespace mpl {

template <class Type>
struct identity {
    typedef Type type;
};

}} // namespace shand::mpl

#endif // SHAND_MPL_IDENTITY_INCLUDE

