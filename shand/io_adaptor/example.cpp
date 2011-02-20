#include <shand/io_adaptor/io.hpp>
#include <shand/io_adaptor/adapted/std_vector.hpp>

#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<int> > v = {{1, 2}, {3, 4}, {5, 6}};

    using namespace shand::io_adaptors::operators;
    std::cout << v << std::endl;
}


