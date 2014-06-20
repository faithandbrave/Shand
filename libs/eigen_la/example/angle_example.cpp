#include <iostream>
#include <shand/eigen_la.hpp>
#include <shand/strong_typedef/tagged_real_io.hpp>

int main()
{
    const shand::la::vector2<float> p(0.0f, 0.0f);
    const shand::la::vector2<float> direction(0.0f, 1.0f);
    const shand::la::vector2<float> q(1.0f, 1.0f);

    // use dot
    {
        const shand::radian_f theta = shand::la::vector_angle(direction, q);
        std::cout << shand::angle_cast<shand::degree_f>(theta) << std::endl;
    }

    // use atan2
    {
        const shand::la::vector2<float> v = (q - p).normalized();
        const shand::radian_f theta = shand::atan2(v.y(), v.x());
        std::cout << shand::angle_cast<shand::degree_f>(theta) << std::endl;
    }

    // use matrix
    {
        const shand::la::vector2<float> v = (q - p).normalized();

        const shand::la::rotation2d<float> rotate = shand::la::make_rotation2d(v);
        const shand::radian_f theta = rotate.angle();

        std::cout << shand::angle_cast<shand::degree_f>(theta) << std::endl;
    }
}

/*
result:
45
45
45
*/
