#ifndef SHAND_SPIRIT_QI_VALID_CHECK_INCLUDE
#define SHAND_SPIRIT_QI_VALID_CHECK_INCLUDE

#include <boost/spirit/include/qi.hpp>

namespace shand { namespace spirit_qi {

template <class Expr>
struct valid_check_t {
    Expr expr;
 
    valid_check_t(const Expr& expr_)
        : expr(expr_) {}
 
    template <class T>
    void operator()(const T& x, boost::spirit::unused_type, bool& pass) const
    {
        pass = expr(x);
    }
};

template <class Expr>
inline valid_check_t<Expr> valid_check(const Expr& expr)
{
    return valid_check_t<Expr>(expr);
}

}} // namespace shand::spirit_qi

#endif // SHAND_SPIRIT_QI_VALID_CHECK_INCLUDE


