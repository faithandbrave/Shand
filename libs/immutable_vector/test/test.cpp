// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/immutable_vector.hpp>

shand::vector_builder<int> data() { return {1, 2, 3}; }

void test_construct()
{
    shand::immutable_vector<int> v(data());
    BOOST_TEST(v.get() == data());
}

void test_build()
{
    shand::immutable_vector<int> v;
    v.build(data());

    BOOST_TEST(v.get() == data());
}

void test_iterator()
{
    shand::immutable_vector<int> v(data());

    // pass test
    decltype(v)::iterator begin = v.begin();
    decltype(v)::iterator end = v.end();
    BOOST_TEST(end - begin == static_cast<decltype(v)::difference_type>(v.size()));

    decltype(v)::const_iterator cbegin = v.cbegin();
    decltype(v)::const_iterator cend = v.cend();
    BOOST_TEST(cend - cbegin == static_cast<decltype(v)::difference_type>(v.size()));
}

void test_size()
{
    shand::immutable_vector<int> v(data());
    BOOST_TEST(v.size() == 3u);
}

void test_empty()
{
    shand::immutable_vector<int> v(data());
    BOOST_TEST(!v.empty());

    shand::immutable_vector<int> e;
    BOOST_TEST(e.empty());
}

void test_at()
{
    shand::immutable_vector<int> v(data());

    BOOST_TEST(v[0] == 1);
    BOOST_TEST(v[1] == 2);
    BOOST_TEST(v[2] == 3);

    BOOST_TEST(v.at(0) == 1);
    BOOST_TEST(v.at(1) == 2);
    BOOST_TEST(v.at(2) == 3);
    try {
        v.at(3);
        BOOST_TEST(false);
    }
    catch (std::out_of_range&) {
        BOOST_TEST(true);
    }

    boost::optional<const int&> front = v.opt_at(0);
    BOOST_TEST(front.get() == 1);

    boost::optional<const int&> center = v.opt_at(1);
    BOOST_TEST(center.get() == 2);

    boost::optional<const int&> back = v.opt_at(2);
    BOOST_TEST(back.get() == 3);

    boost::optional<const int&> out = v.opt_at(3);
    BOOST_TEST(out == boost::none);
}

void test_front()
{
    {
        shand::immutable_vector<int> v(data());
        boost::optional<const int&> front = v.opt_front();
        BOOST_TEST(front.get() == 1);
    }
    {
        shand::immutable_vector<int> v;
        boost::optional<const int&> front = v.opt_front();
        BOOST_TEST(front == boost::none);
    }
}

void test_back()
{
    {
        shand::immutable_vector<int> v(data());
        boost::optional<const int&> back = v.opt_back();
        BOOST_TEST(back.get() == 3);
    }
    {
        shand::immutable_vector<int> v;
        boost::optional<const int&> back = v.opt_back();
        BOOST_TEST(back == boost::none);
    }
}

void test_data()
{
    shand::immutable_vector<int> v(data());
    const int* p = v.data();
    BOOST_TEST(p);
    BOOST_TEST(*p == 1);
}

int main()
{
    test_construct();
    test_build();
    test_iterator();
    test_size();
    test_empty();
    test_at();
    test_front();
    test_back();
    test_data();

    return boost::report_errors();
}

