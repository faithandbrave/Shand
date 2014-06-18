#ifndef SHAND_EIGEN_VECTOR_INCLUDE
#define SHAND_EIGEN_VECTOR_INCLUDE

// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cmath>
#include <shand/angle.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/constants/constants.hpp>
#include <Eigen/Core>

namespace shand { namespace la {

template <class T, int Dimension>
using vector = Eigen::Matrix<T, Dimension, 1>;

template <class T>
using vector2 = vector<T, 2>;

template <class T>
using vector3 = vector<T, 3>;

template <class T, int Dimension>
radian_t<T> vector_angle(const ::shand::la::vector<T, Dimension>& v,
                         const ::shand::la::vector<T, Dimension>& u)
{
    const T length = v.norm() * u.norm();
    if (boost::geometry::math::equals(length, static_cast<T>(0.0))) {
        return radian_t<T>(0.0);
    }

    const T x = v.dot(u) / length;
    const T rounded = boost::algorithm::clamp(x, static_cast<T>(-1.0), static_cast<T>(1.0));
    return radian_t<T>(std::acos(rounded));
}

}} // namespace shand::la

#endif // SHAND_EIGEN_VECTOR_INCLUDE

