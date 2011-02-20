#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <shand/optional_algorithm/find_if.hpp>

using boost::lambda::_1;

int main()
{
	const std::vector<int> v = boost::assign::list_of(3)(1)(4);
	if (boost::optional<const int&> p = shand::find_if(v, _1 % 2 == 0)) {
		BOOST_TEST(p.get() == 4);
	}
	else {
		BOOST_ERROR("find_if failed!");
	}

	return boost::report_errors();
}

