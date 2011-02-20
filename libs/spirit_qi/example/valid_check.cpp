#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <shand/spirit_qi/valid_check.hpp>
 
namespace qi = boost::spirit::qi;
using namespace boost::lambda;

using shand::spirit_qi::valid_check;
 
int main()
{
    const std::string s = "3";
 
    std::string::const_iterator it = s.begin();
    if (!qi::parse(it, s.end(), qi::int_[valid_check(_1 == 2)])) {
        std::cout << "fail" << std::endl;
    }
    else {
        std::cout << "success" << std::endl;
    }
}
