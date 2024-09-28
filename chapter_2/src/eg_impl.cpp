#include "../include/eg_impl.hpp"

void eg2_1(void)
{
    std::cout << std::scientific << std::setprecision(16) << std::setw(21) << std::setfill('0');

    size_t n_a, n_b, n_complex_a, n_complex_b;

    std::ifstream fp;

    // file a.vec
    fp.open("../input/a.vec");
    assert(fp);

    fp >> n_a;
    std::vector<double> vec_a(n_a);
    for (size_t index = 0; index < n_a; ++index)
    {
        fp >> vec_a[index];
    }

    fp.close();

    // file b.vec
    fp.open("../input/b.vec");
    assert(fp);

    fp >> n_b;
    std::vector<double> vec_b(n_b);
    for (size_t index = 0; index < n_b; ++index)
    {
        fp >> vec_b[index];
    }

    fp.close();

    // file complex_a.vec
    fp.open("../input/complex_a.vec");
    assert(fp);

    fp >> n_complex_a;
    std::vector<std::complex<double>> complex_vec_a(n_complex_a);
    for (size_t index = 0; index < n_complex_a; ++index)
    {
        double val_re, val_im;
        fp >> val_re >> val_im;
        complex_vec_a[index] = std::complex<double>(val_re, val_im);
    }

    fp.close();

    // file complex_b.vec
    fp.open("../input/complex_b.vec");
    assert(fp);

    fp >> n_complex_b;
    std::vector<std::complex<double>> complex_vec_b(n_complex_b);
    for (size_t index = 0; index < n_complex_b; ++index)
    {
        double val_re, val_im;
        fp >> val_re >> val_im;
        complex_vec_b[index] = std::complex<double>(val_re, val_im);
    }

    fp.close();

    // print vector
    std::cout << "vec_a:\n";
    for (size_t index = 0; index < vec_a.size(); ++index)
    {
        std::cout << vec_a[index] << '\n';
    }
    std::cout << '\n';

    std::cout << "vec_b:\n";
    for (size_t index = 0; index < vec_b.size(); ++index)
    {
        std::cout << vec_b[index] << '\n';
    }
    std::cout << '\n';

    std::cout << "complex_vec_a:\n";
    for (size_t index = 0; index < complex_vec_a.size(); ++index)
    {
        std::cout << complex_vec_a[index] << '\n';
    }
    std::cout << '\n';

    std::cout << "complex_vec_b:\n";
    for (size_t index = 0; index < complex_vec_b.size(); ++index)
    {
        std::cout << complex_vec_b[index] << '\n';
    }
    std::cout << '\n';

    // computing inner product
    double inner_product_vec_a_b = 0.;
    assert(n_a == n_b);

    for (size_t index = 0; index < n_a; ++index)
    {
        inner_product_vec_a_b += vec_a[index] * vec_b[index];
    }
    std::cout << "inner product of vec_a and vec_b is: " << inner_product_vec_a_b << '\n';

    std::complex<double> inner_product_complex_a_b(0., 0.);
    assert(n_complex_a == n_complex_b);

    for(size_t index = 0; index < n_complex_a; ++index)
    {
        std::complex<double> val_tmp = std::conj(complex_vec_a[index]);
        inner_product_complex_a_b += complex_vec_b[index] * val_tmp;
    }
    std::cout << "inner product of complex_vec_a and complex_vec_b is: " << inner_product_complex_a_b << '\n';
}