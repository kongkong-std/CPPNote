#include "../include/eg_impl.hpp"

void eg4_1(void)
{
    // vector
    double *x = nullptr, *y = nullptr;

    x = new double[10];
    y = new double[10];
    assert(x != nullptr && y != nullptr);

    for (int index = 0; index < 10; ++index)
    {
        x[index] = index;
        y[index] = 2. * index;
    }

    std::cout << "==== print vector x, y:\n";
    std::cout << "vector x:\n";
    for (int index = 0; index < 10; ++index)
    {
        std::cout << x[index] << '\n';
    }
    std::cout << "vector y:\n";
    for (int index = 0; index < 10; ++index)
    {
        std::cout << y[index] << '\n';
    }

    // free memory
    delete[] x;
    delete[] y;

    // matrix
    /*
     * matrix size 5 x 6
     */
    double **mat = nullptr;
    mat = new double *[5];
    assert(mat != nullptr);
    for (int index = 0; index < 5; ++index)
    {
        mat[index] = new double[6];
        assert(mat[index] != nullptr);
    }

    for (int index_i = 0; index_i < 5; ++index_i)
    {
        for (int index_j = 0; index_j < 6; ++index_j)
        {
            mat[index_i][index_j] = index_i + index_j;
        }
    }

    std::cout << "==== print matrix mat:\n";
    for (int index_i = 0; index_i < 5; ++index_i)
    {
        for (int index_j = 0; index_j < 6; ++index_j)
        {
            std::cout << mat[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    // free memory
    for (int index = 0; index < 5; ++index)
    {
        delete[] mat[index];
    }
    delete[] mat;
}
