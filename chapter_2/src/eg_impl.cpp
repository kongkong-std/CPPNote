#include "../include/eg_impl.hpp"

double ex2_6_f(double);  // f = exp(x) + x^3 - 5
double ex2_6_df(double); // f' = exp(x) + 3 x^2

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

    for (size_t index = 0; index < n_complex_a; ++index)
    {
        std::complex<double> val_tmp = std::conj(complex_vec_a[index]);
        inner_product_complex_a_b += complex_vec_b[index] * val_tmp; // <vec_a, vec_b> = vec_a^H vec_b
    }
    std::cout << "inner product of complex_vec_a and complex_vec_b is: " << inner_product_complex_a_b << '\n';
}

void ex2_1(void)
{
    double x = 0., y = 0., z = 0.;
    std::cout << "input numbers:\n";
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    if ((x > y) || (x < 5.))
    {
        z = 4.;
    }
    else
    {
        z = 2.;
    }

    std::cout << "z = " << z << '\n';
}

void ex2_4(void)
{
    size_t n_vec_u, n_vec_v;
    size_t m_mat_a, n_mat_a;
    size_t m_mat_b, n_mat_b;

    std::ifstream fp;

    // file ex2_4_u.vec
    fp.open("../input/ex2_4_u.vec");
    assert(fp);

    fp >> n_vec_u;
    std::vector<double> vec_u(n_vec_u);
    for (size_t index = 0; index < n_vec_u; ++index)
    {
        fp >> vec_u[index];
    }
    fp.close();

    // file ex2_4_v.vec
    fp.open("../input/ex2_4_v.vec");
    assert(fp);

    fp >> n_vec_v;
    std::vector<double> vec_v(n_vec_v);
    for (size_t index = 0; index < n_vec_v; ++index)
    {
        fp >> vec_v[index];
    }
    fp.close();

    // file ex2_4_A.mat
    fp.open("../input/ex2_4_A.mat");
    assert(fp);

    fp >> m_mat_a >> n_mat_a;
    std::vector<std::vector<double>> mat_a(m_mat_a, std::vector<double>(n_mat_a, 0.));
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            fp >> mat_a[index_i][index_j];
        }
    }
    fp.close();

    // file ex2_4_B.mat
    fp.open("../input/ex2_4_B.mat");
    assert(fp);

    fp >> m_mat_b >> n_mat_b;
    std::vector<std::vector<double>> mat_b(m_mat_b, std::vector<double>(n_mat_b, 0.));
    for (size_t index_i = 0; index_i < m_mat_b; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_b; ++index_j)
        {
            fp >> mat_b[index_i][index_j];
        }
    }
    fp.close();

    // print vector and matrix
    std::cout << "vec_u:\n";
    for (size_t index = 0; index < n_vec_u; ++index)
    {
        std::cout << vec_u[index] << '\n';
    }

    std::cout << "vec_v:\n";
    for (size_t index = 0; index < n_vec_v; ++index)
    {
        std::cout << vec_v[index] << '\n';
    }

    std::cout << "mat_a:\n";
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            std::cout << mat_a[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    std::cout << "mat_b:\n";
    for (size_t index_i = 0; index_i < m_mat_b; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_b; ++index_j)
        {
            std::cout << mat_b[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    // vec_x = vec_u - vec_v
    assert(n_vec_u == n_vec_v);
    std::vector<double> vec_x(n_vec_u);
    for (size_t index = 0; index < n_vec_u; ++index)
    {
        vec_x[index] = vec_u[index] - vec_v[index];
    }

    // vec_y = A u
    assert(n_mat_a == n_vec_u);
    std::vector<double> vec_y(m_mat_a);
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        double tmp = 0;
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            tmp += mat_a[index_i][index_j] * vec_u[index_j];
        }
        vec_y[index_i] = tmp;
    }

    // vec_z = Au - v
    assert(m_mat_a == n_vec_v);
    std::vector<double> vec_z(m_mat_a);
    for (size_t index = 0; index < m_mat_a; ++index)
    {
        vec_z[index] = vec_y[index] - vec_v[index];
    }

    // mat_c = 4 * mat_a - 3 * mat_b
    assert(m_mat_a == m_mat_b);
    assert(n_mat_a == n_mat_b);
    std::vector<std::vector<double>> mat_c(m_mat_a, std::vector<double>(n_mat_a, 0.));
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            mat_c[index_i][index_j] = 4 * mat_a[index_i][index_j] - 3 * mat_b[index_i][index_j];
        }
    }

    // mat_d = mat_a * mat_b
    assert(n_mat_a == m_mat_b);
    std::vector<std::vector<double>> mat_d(m_mat_a, std::vector<double>(n_mat_b, 0.));
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_b; ++index_j)
        {
            double tmp = 0;
            for (size_t index_k = 0; index_k < n_mat_a; ++index_k)
            {
                tmp += mat_a[index_i][index_k] * mat_b[index_k][index_j];
            }
            mat_d[index_i][index_j] = tmp;
        }
    }

    // print value
    std::cout << "vec_x:\n";
    for (size_t index = 0; index < n_vec_u; ++index)
    {
        std::cout << vec_x[index] << '\n';
    }

    std::cout << "vec_y:\n";
    for (size_t index = 0; index < m_mat_a; ++index)
    {
        std::cout << vec_y[index] << '\n';
    }

    std::cout << "vec_z:\n";
    for (size_t index = 0; index < m_mat_a; ++index)
    {
        std::cout << vec_z[index] << '\n';
    }

    std::cout << "mat_c:\n";
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            std::cout << mat_c[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    std::cout << "mat_d:\n";
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_b; ++index_j)
        {
            std::cout << mat_d[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }
}

/*
 * inversion matrix
 */
void ex2_5(void)
{
    size_t m_mat_a, n_mat_a;

    std::ifstream fp;
    fp.open("../input/ex2_5_A.mat");

    fp >> m_mat_a >> n_mat_a;
    assert(m_mat_a == n_mat_a);
    std::vector<std::vector<double>> mat_a(m_mat_a, std::vector<double>(n_mat_a, 0.));
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            fp >> mat_a[index_i][index_j];
        }
    }
    fp.close();

    // print mat_a
    std::cout << "mat_a:\n";
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            std::cout << mat_a[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    double det_mat_a = mat_a[0][0] * mat_a[1][1] - mat_a[0][1] * mat_a[1][0];
    assert(det_mat_a != 0);
    std::cout << "determinent of mat_a = " << det_mat_a << '\n';

    std::vector<std::vector<double>> inv_mat_a(m_mat_a, std::vector<double>(n_mat_a, 0.));
    inv_mat_a[0][0] = mat_a[1][1] / det_mat_a;
    inv_mat_a[0][1] = -mat_a[0][1] / det_mat_a;
    inv_mat_a[1][0] = -mat_a[1][0] / det_mat_a;
    inv_mat_a[1][1] = mat_a[0][0] / det_mat_a;

    // print inv_mat_a
    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_a; ++index_j)
        {
            std::cout << inv_mat_a[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }
}

/*
 * newtown-raphson iteration
 */
void ex2_6(void)
{
    double x_sol = 0.;
    double tol = 1e-8;
    int iter = 0, max_it = 100;
    std::vector<double> residual;
    residual.push_back(fabs(ex2_6_f(x_sol)));

    while (iter < max_it && fabs(ex2_6_f(x_sol)) > tol)
    {
        x_sol = x_sol - ex2_6_f(x_sol) / ex2_6_df(x_sol);
        residual.push_back(fabs(ex2_6_f(x_sol)));
        ++iter;
    }

    std::cout << "numerical solution: " << x_sol << '\n';
    std::cout << "itertaion time: " << iter << '\n';
    for (size_t index = 0; index < residual.size(); ++index)
    {
        std::cout << index << '\t' << residual[index] << '\n';
    }
}

double ex2_6_f(double x)
{
    return exp(x) + x * x * x - 5;
}

double ex2_6_df(double x)
{
    return exp(x) + 3 * x * x;
}
