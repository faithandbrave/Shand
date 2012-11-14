// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <shand/strong_typedef/tagged_real.hpp>

struct degree_tag {};
struct radian_tag {};

template <class T>
using degree = shand::tagged_real<T, degree_tag>;

template <class T>
using radian = shand::tagged_real<T, radian_tag>;

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
    // �قȂ�^(�^�O)�Ԃł̈Öٕϊ��͂ł��Ȃ�
    {
        degree<float> deg(90.0f);
//      radian<float> rad = deg; // �R���p�C���G���[�I�^���Ⴄ
    }

    // degree����radian�ւ̕ϊ�
    {
        degree<float> deg(90.0f);
        radian<float> rad = degree_to_radian(deg);
        std::cout << rad.get() << std::endl;
    }

    // radian����degree�ւ̕ϊ�
    {
        radian<float> rad(0.5 * boost::math::constants::pi<float>());
        degree<float> deg = radian_to_degree(rad);
        std::cout << deg.get() << std::endl;
    }
}

/*
output:
1.5708
90
*/

