#include "../include/eg_impl.hpp"

void ComplexNumberRealImaginaryPart(double, double,
                                    double & /*real part*/, double & /*imaginary part*/);

double FunctionF(double x, double K);
double DFunctionF(double x); // dxF

void NewtonRaphsonRootF(double &x /*numerical solution*/, double K,
                        double tol = 1e-6 /*criterion*/, int max_it = 100 /*maximum iteration*/);

void ScaleFunction(double *y /*scaled vector*/, const double *x /*original vector*/,
                   double scale = 0. /*scaler*/, int n = 0 /*size*/); // vector data
void ScaleFunction(double **mat_b /*scaled matrix*/, const double *const *mat_a /*original matrix*/,
                   double scale = 0. /*scaler*/, int n = 0 /*size*/); // matrix data, function overloading

double SineFunction(double x = 0.); // return sin(x)

double ExpFunction(double x = 0.); // return e^x

double FunctionSqrtX10(double x); // f(x) = sqrt(x) - 10

double FunctionDSqrtX10(double x); // df(x) = 1 / 2 / sqrt(x)

double FunctionCubeX10(double x); // f(x) = x^3 - 10

double FunctionDCubeX10(double x); // df(x) = 3 x^2

double NewtonRaphsonSolution(double (*p_fun)(double) /*original function*/,
                             double (*p_dfun)(double) /*differential original function*/,
                             double x /*initial guess*/,
                             double tol = 1e-8 /*criterion*/,
                             int max_it = 100 /*maximum iteration*/);

void eg5_5(void)
{
    double sol = 0.;
    std::cout << "solution of sqrt(x) = 10, with initial guess 1.0:\n";
    sol = NewtonRaphsonSolution(FunctionSqrtX10, FunctionDSqrtX10, 1.);
    std::cout << "numerical solution: " << sol << '\n';

    std::cout << "\nsolution of x^3 = 10, with initial guess 1.0:\n";
    sol = NewtonRaphsonSolution(FunctionCubeX10, FunctionDCubeX10, 1.);
    std::cout << "numerical solution: " << sol << '\n';
}

double NewtonRaphsonSolution(double (*p_fun)(double),
                             double (*p_dfun)(double),
                             double x,
                             double tol,
                             int max_it)
{
    std::cout << "iteration\tresidual\n";

    int iter = 0;
    double resid = fabs(p_fun(x));
    std::cout << iter << "\t" << resid << '\n';

    while ((iter < max_it) && (resid > tol))
    {
        x -= p_fun(x) / p_dfun(x);
        ++iter;
        resid = fabs(p_fun(x));
        std::cout << iter << '\t' << resid << '\n';
    }

    return x;
}

double FunctionSqrtX10(double x)
{
    return sqrt(x) - 10.;
}

double FunctionDSqrtX10(double x)
{
    return 1. / 2. / sqrt(x);
}

double FunctionCubeX10(double x)
{
    return x * x * x - 10.;
}

double FunctionDCubeX10(double x)
{
    return 3 * x * x;
}

void eg5_4(void)
{
    double (*p_fun)(double x);

    p_fun = &SineFunction;
    std::cout << "sin(x):\n";
    std::cout << p_fun(1.) << '\n';

    p_fun = &ExpFunction;
    std::cout << "e^x:\n";
    std::cout << p_fun(1.) << '\n';
}

double SineFunction(double x)
{
    return sin(x);
}

double ExpFunction(double x)
{
    return exp(x);
}

void eg5_3(void)
{
    int n = 5;          // size
    double scale = 1.1; // scaling number
    double *x = nullptr, *y = nullptr;
    x = new double[n];
    y = new double[n];
    assert(x != nullptr && y != nullptr);
    std::cout << "vector data:\n";
    std::cout << "vector x:\n";
    std::iota(x, x + n, 0.);
    for (int index = 0; index < n; ++index)
    {
        std::cout << x[index] << '\n';
    }
    std::cout << "after scaling " << scale << ", vector y:\n";
    ScaleFunction(y, x, scale, n);
    for (int index = 0; index < n; ++index)
    {
        std::cout << y[index] << '\n';
    }

    double **mat_a = nullptr, **mat_b = nullptr;
    mat_a = new double *[n];
    mat_b = new double *[n];
    assert(mat_a != nullptr && mat_b != nullptr);
    for (int index = 0; index < n; ++index)
    {
        mat_a[index] = new double[n];
        mat_b[index] = new double[n];
        assert(mat_a[index] != nullptr && mat_b[index] != nullptr);
    }
    for (int index = 0; index < n; ++index)
    {
        std::iota(*(mat_a + index), *(mat_a + index) + n, (double)+index);
    }
    std::cout << "matrix data:\n";
    std::cout << "matrix a:\n";
    for (int index_i = 0; index_i < n; ++index_i)
    {
        for (int index_j = 0; index_j < n; ++index_j)
        {
            std::cout << mat_a[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }
    ScaleFunction(mat_b, mat_a, scale, n);
    std::cout << "after scaling " << scale << ", matrix b:\n";
    for (int index_i = 0; index_i < n; ++index_i)
    {
        for (int index_j = 0; index_j < n; ++index_j)
        {
            std::cout << mat_b[index_i][index_j] << '\t';
        }
        std::cout << '\n';
    }
}

void ScaleFunction(double **mat_b, const double *const *mat_a, double scale, int n)
{
    for (int index_i = 0; index_i < n; ++index_i)
    {
        for (int index_j = 0; index_j < n; ++index_j)
        {
            mat_b[index_i][index_j] = scale * mat_a[index_i][index_j];
        }
    }
}

void ScaleFunction(double *y, const double *x, double scale, int n)
{
    for (int index = 0; index < n; ++index)
    {
        y[index] = scale * x[index];
    }
}

void eg5_2(void)
{
    std::cout << std::scientific << std::setprecision(16) << std::setw(21) << std::setfill('0');
    // Newtown-Raphson method
    /*
     * x_n = x_n-1 - (x_n-1^3 - K) / 3 / x_n-1^2
     */
    double x = 1.;  // initial guess
    double K = 12.; // f(x) = x^3 - K = 0

    std::cout << "Newton-Raphson iteration with default criterion and maximum iteration:\n";
    NewtonRaphsonRootF(x, K);
    std::cout << "numerical solution: " << x << '\n';

    x = 1.;
    double tol = 1.e-10;
    std::cout << "Newton-Raphson iteration with criterion " << tol << ":\n";
    NewtonRaphsonRootF(x, K, tol); // argument order corresponding to function declaration
    std::cout << "numerical solution: " << x << '\n';
}

void NewtonRaphsonRootF(double &x, double K, double tol, int max_it)
{
    int iter = 0;
    double resid = fabs(FunctionF(x, K)); // residual |f(x)|

    std::cout << "iteration " << iter << "\t absolute residual " << resid << '\n';

    while ((resid > tol) && iter < max_it)
    {
        /* code */
        ++iter;
        x -= FunctionF(x, K) / DFunctionF(x);
        resid = fabs(FunctionF(x, K));
        std::cout << "iteration " << iter << "\t absolute residual " << resid << '\n';
    }
}

double FunctionF(double x, double K)
{
    return x * x * x - K;
}

double DFunctionF(double x)
{
    return 3 * x * x;
}

void eg5_1(void)
{
    double r = 3.4;
    double theta = 1.23;
    double x = 0, y = 0;
    std::cout << "value of x, y:\n";
    std::cout << "x = " << x << ", y = " << y << '\n';

    std::cout << "after calling function with reference variables...\n";
    ComplexNumberRealImaginaryPart(r, theta, x, y);
    std::cout << "x = " << x << ", y = " << y << '\n';
}

void ComplexNumberRealImaginaryPart(double r, double theta, double &a, double &b)
{
    a = r * cos(theta);
    b = r * sin(theta);
}
