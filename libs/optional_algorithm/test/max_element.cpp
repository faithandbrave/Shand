#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <shand/optional_algorithm/max_element.hpp>

int main()
{
	const std::vector<int> v = boost::assign::list_of(3)(1)(4);
	if (boost::optional<const int&> p = shand::max_element(v)) {
		BOOST_TEST(p.get() == 1);
	}
	else {
		BOOST_ERROR("max_element failed! Though the element exists.");
	}

	const std::vector<int> v2;
	if (boost::optional<const int&> p = shand::max_element(v2)) {
		BOOST_ERROR("max_element must not successed. range is empty.");
	}
	else {
		BOOST_TEST(true);
	}

	return boost::report_errors();
}

