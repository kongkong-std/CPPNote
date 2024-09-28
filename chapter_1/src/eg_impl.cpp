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

/*
 * math function
 */
void eg1_3(void)
{
    double x = 1., y = 2., z;
    z = x / y;
    std::cout << "ratio of " << x << " and " << y << " is " << z << '\n';

    z = x * y;
    std::cout << "product of " << x << " and " << y << " is " << z << '\n';

    z = sqrt(x);
    std::cout << "square root of " << x << " is " << z << '\n';

    z = sqrt(y);
    std::cout << "square root of " << y << " is " << z << '\n';

    z = exp(x);
    std::cout << "exponential function of " << x << " is " << z << '\n';

    z = exp(y);
    std::cout << "exponential function of " << y << " is " << z << '\n';

    z = pow(x, y);
    std::cout << "power of " << x << " and " << y << " is " << z << '\n';

    z = pow(y, x);
    std::cout << "power of " << y << " and " << x << " is " << z << '\n';

    z = M_PI;
    std::cout << "pi = " << z << '\n';

    x = 7.8;
    y = 1.65;
    double u = -3.4;

    z = fmod(x, y);
    std::cout << "module of " << x << " and " << y << " is " << z << '\n';

    z = fmod(y, x);
    std::cout << "module of " << y << " and " << x << " is " << z << '\n';

    z = fabs(u);
    std::cout << "absolute value of " << u << " is " << z << '\n';

    z = atan2(x, y);
    std::cout << "inverse tangent of (" << x << ", " << y << ") is " << z << '\n';

    z = atan2(-x, y);
    std::cout << "inverse tangent of (" << -x << ", " << y << ") is " << z << '\n';

    z = atan2(-x, -y);
    std::cout << "inverse tangent of (" << -x << ", " << -y << ") is " << z << '\n';

    z = atan2(x, -y);
    std::cout << "inverse tangent of (" << x << ", " << -y << ") is " << z << '\n';

    int a = 1, b = 2;
    z = (double)a / b; // type convert
    std::cout << "z = " << z << '\n';
}

/*
 * character and string
 */
void eg1_4(void)
{
    bool flag1, flag2;
    char letter;
    flag1 = true;
    flag2 = false;

    if (flag1)
    {
        letter = 'T';
        std::cout << letter << '\n';
    }
    if (!flag2)
    {
        letter = 'F';
        std::cout << letter << '\n';
    }

    std::string city;
    city = "beijing";
    std::cout << "String length = " << city.length() << '\n';
    std::cout << "first character = " << city.at(0) << '\n';
    std::cout << "first character = " << city[0] << '\n';
    std::cout << city << '\n';
    std::cout << city.c_str() << '\n';
    city.append(" hhhh");
    std::cout << "String length = " << city.length() << '\n';
    std::cout << city << '\n';
    city.push_back('a');
    std::cout << "String length = " << city.length() << '\n';
    std::cout << city << '\n';

    std::string *city2 = nullptr;
    city2 = new std::string;
    *city2 = "shanghai";
    std::cout << "String length = " << city2->length() << '\n';
    std::cout << "first character = " << city2->at(0) << '\n';
    std::cout << "first character = " << (*city2)[0] << '\n';
    std::cout << "first character = " << city2[0] << '\n';
    // std::cout << "first character = " << city2[1] << '\n';
    std::cout << city2 << '\n';
    std::cout << *city2 << '\n';
    std::cout << city2->c_str() << '\n';
    city2->append(" yyyy");
    std::cout << *city2 << "\a\a\a\n";

    std::string line;
    std::cout << "Enter a line: ";
    std::getline(std::cin, line);
    std::cout << "type: " << line << '\n';
}

/*
 * assert
 */
void eg1_5(void)
{
    double a;
    std::cout << "enter a non-negative number: ";
    std::cin >> a;
    assert(a >= 0.0);
    std::cout << "square root = " << sqrt(a) << '\n';
}

/*
 * matrix-by-matrix product
 *     mat1 = [1.1 1.2 1.3;
 *             2.1 2.2 2.3;
 *             3.1 3.2 3.3];
 *
 *     mat2 = [1 2 3;
 *             4 5 6;
 *             7 8 9];
 */
void ex1_4(void)
{
    std::vector<std::vector<double>> mat_a;
    std::vector<std::vector<double>> mat_b;
    std::vector<std::vector<double>> mat_c; // mat_c = mat_a * mat_b

    std::ifstream fp("../input/a.mat");
    assert(fp);

    std::string line;
    while (std::getline(fp, line))
    {
        std::vector<double> row;
        std::istringstream iss(line); // string line to istringstream
        double value;
        while (iss >> value) // get value from iss
        {
            row.push_back(value);
        }
        mat_a.push_back(row);
    }

    fp.close();

    fp.open("../input/b.mat");
    assert(fp);

    while (std::getline(fp, line))
    {
        std::vector<double> row;
        std::istringstream iss(line); // string line to istringstream
        double value;
        while (iss >> value) // get value from iss
        {
            row.push_back(value);
        }
        mat_b.push_back(row);
    }

    fp.close();

    // print matrix
    std::cout << "\n==== mat_a:\n";
    for (size_t index_i = 0; index_i < mat_a.size(); ++index_i)
    {
        for (size_t index_j = 0; index_j < mat_a[index_i].size(); ++index_j)
        {
            std::cout << mat_a[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    std::cout << "\n==== mat_b:\n";
    for (size_t index_i = 0; index_i < mat_b.size(); ++index_i)
    {
        for (size_t index_j = 0; index_j < mat_b[index_i].size(); ++index_j)
        {
            std::cout << mat_b[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }

    // matrix-by-matrix product
    size_t m_mat_a = mat_a.size(), n_mat_a = mat_a[0].size();
    size_t m_mat_b = mat_b.size(), n_mat_b = mat_b[0].size();
    assert(n_mat_a == m_mat_b); // reasonable size

    mat_c.resize(m_mat_a, std::vector<double>(n_mat_b, 0.));

    for (size_t index_i = 0; index_i < m_mat_a; ++index_i)
    {
        for (size_t index_j = 0; index_j < n_mat_b; ++index_j)
        {
            double tmp = 0;
            for (size_t index_k = 0; index_k < n_mat_a; ++index_k)
            {
                tmp += mat_a[index_i][index_k] * mat_b[index_k][index_j];
            }
            mat_c[index_i][index_j]= tmp;
        }
    }

    std::cout << "\n==== mat_c:\n";
    for (size_t index_i = 0; index_i < mat_c.size(); ++index_i)
    {
        for (size_t index_j = 0; index_j < mat_c[index_i].size(); ++index_j)
        {
            std::cout << mat_c[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }
}
