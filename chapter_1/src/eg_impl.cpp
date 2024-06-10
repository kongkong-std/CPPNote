#include "../include/eg_impl.hpp"

void eg1_1(void)
{
    std::cout << "hello, the world!\n";
}

/*
 * variables
 */
void eg1_2(void)
{
    std::cout << "sizeof char = " << sizeof(char) << " bytes\n";
    std::cout << "sizeof short = " << sizeof(short) << " bytes\n";
    std::cout << "sizeof int = " << sizeof(int) << " bytes\n";
    std::cout << "sizeof unsigned int = " << sizeof(unsigned int) << " bytes\n";
    std::cout << "sizeof long int = " << sizeof(long int) << " bytes\n";
    std::cout << "sizeof float = " << sizeof(float) << " bytes\n";
    std::cout << "sizeof double = " << sizeof(double) << " bytes\n";

    int a = 0, b = 1;
    std::cout << "initial a = " << a << ", b = " << b << "\n";

    a = b = 2;
    std::cout << "after a = b = 2, a = " << a << ", b = " << b << "\n";

    (a = b) = 3;
    std::cout << "after (a = b) = 3, a = " << a << ", b = " << b << "\n";

    a = (b = 4);
    std::cout << "after a = (b = 4), a = " << a << ", b = " << b << "\n";

    double tol = 1e-13, ratio = 0.3;
    std::cout << "tol = " << tol << ", ratio = " << ratio << "\n";
    std::cout << "point number: " << std::setw(20) << std::setfill('-') << tol << "\n";
    std::cout << "point number: " << std::setprecision(18) << tol << ratio << "\n";
    std::cout << "fixed point number: " << std::fixed << tol << "\n";
    std::cout << "scientific point number: " << std::scientific << std::setprecision(6) << ratio << "\n";

    std::cout << "size of a = " << sizeof(a) << "\n";
    std::cout << "size of b = " << sizeof(b) << "\n";
    std::cout << "size of tol = " << sizeof(tol) << "\n";
    std::cout << "size of ratio = " << sizeof(ratio) << "\n";
}