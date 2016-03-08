// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/math/constants/constants.hpp>
#include <shand/strong_typedef/tagged_float.hpp>
#include <shand/strong_typedef/tagged_float_io.hpp>

struct degree_tag {};
struct radian_tag {};

template <class T>
using degree = shand::tagged_float<T, degree_tag>;

template <class T>
using radian = shand::tagged_float<T, radian_tag>;

template <class T>
radian<T> degree_to_radian(const degree<T>& x)
{
    return radian<T>(x.get() * boost::math::constants::pi<T>() / static_cast<T>(180.0));
}

template <class T>
degree<T> radian_to_degree(const radian<T>& x)
{
    return degree<T>(x.get() * static_cast<T>(180.0) / boost::math::constants::pi<T>());
}

int main ()
{
    // 異なる型(タグ)間での暗黙変換はできない
    {
        degree<float> deg(90.0f);
//      radian<float> rad = deg; // コンパイルエラー！型が違う
    }

    // degreeからradianへの変換
    {
        degree<float> deg(90.0f);
        radian<float> rad = degree_to_radian(deg);
        std::cout << rad << std::endl;
    }

    // radianからdegreeへの変換
    {
        radian<float> rad(0.5 * boost::math::constants::pi<float>());
        degree<float> deg = radian_to_degree(rad);
        std::cout << deg << std::endl;
    }
}

/*
output:
1.5708
90
*/

