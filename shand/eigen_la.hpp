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
#include <Eigen/Geometry>

namespace shand { namespace la {

template <class T, int Dimension>
using vector = Eigen::Matrix<T, Dimension, 1>;

template <class T>
using vector2 = vector<T, 2>;

template <class T>
using vector3 = vector<T, 3>;

template <class T>
using matrix2 = Eigen::Matrix<T, 2, 2>;

template <class T>
using matrix3 = Eigen::Matrix<T, 3, 3>;

template <class T>
using matrix4 = Eigen::Matrix<T, 4, 4>;

template <class T>
using rotation2d = Eigen::Rotation2D<T>;

// caution : erase sign
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

template <class T>
::shand::la::matrix2<T> make_rotate2d_matrix(const ::shand::la::vector2<T>& v)
{
    ::shand::la::matrix2<T> m;
    m <<
        v.x() /*cosθ*/, -v.y(), /*-sinθ*/
        v.y() /*sinθ*/,  v.x(); /*sinθ*/
    return m;
}

template <class T>
::shand::la::rotation2d<T> make_rotation2d(const ::shand::la::matrix2<T>& m)
{
	shand::la::rotation2d<float> rotate(0.0f);
    rotate.fromRotationMatrix(m);
	return rotate;
}

template <class T>
::shand::la::rotation2d<T> make_rotation2d(const ::shand::la::vector2<T>& v)
{
	return make_rotation2d(::shand::la::make_rotate2d_matrix(v));
}

}} // namespace shand::la

#endif // SHAND_EIGEN_VECTOR_INCLUDE

