#include <iostream>
#include <shand/eigen_vector.hpp>

int main()
{
    const shand::la::vector<float, 2> v(1.0f, 0.0f);
    const shand::la::vector<float, 2> u(1.0f, 1.0f);

    const shand::radian_f result = shand::la::vector_angle(v, u);
    std::cout << result.get() << std::endl;
    std::cout << shand::angle_cast<shand::degree_f>(result).get() << std::endl;
}

/*
result:

0.785398
45
*/
