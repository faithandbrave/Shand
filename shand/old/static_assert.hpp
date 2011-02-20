#ifndef SHAND_STATIC_ASSERT_INCLUDE
#define SHAND_STATIC_ASSERT_INCLUDE

namespace shand {

template <bool> struct static_assertion_faire;
template <> struct static_assertion_faire<true> { enum { value = 1 }; };

#define SHAND_STATIC_ASSERT(Expression) shand::static_assertion_faire<Expression>::value

} // namespace shand

#endif // SHAND_STATIC_ASSERT_INCLUDE

