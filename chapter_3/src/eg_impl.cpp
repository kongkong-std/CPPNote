#include "../include/eg_impl.hpp"

void function_true(std::vector<double> & /*true solution*/,
                   const std::vector<double> & /*grid x*/);
void backward_euler_sol(std::vector<double> & /*numerical solution*/,
                        const std::vector<double> & /*diagonal*/,
                        const std::vector<double> & /*down diagonal*/,
                        const std::vector<double> & /*rhs vector*/);

/*
 * backward Euler method
 *     dy / dx = -y,    y(0) = 1
 *     x \in (0, 1)
 */
void ex3_3(int *p_argc, char ***p_argv)
{
    std::cout << std::scientific << std::setprecision(16) << std::setw(21) << std::setfill('0');

    int argc = *p_argc;
    char **argv = *p_argv;
    int N = 0;
    double a = 0., b = 0.;
    for (int index = 0; index < argc; ++index)
    {
        // std::cout << "Argument " << index << " = " << argv[index] << '\n';
        if (std::string(argv[index]) == "-N")
        {
            N = atoi(argv[index + 1]);
            std::cout << ">>>> mesh size = " << N << '\n';
        }
        if (std::string(argv[index]) == "-a")
        {
            a = atof(argv[index + 1]);
            std::cout << ">>>> interval a = " << a << '\n';
        }
        if (std::string(argv[index]) == "-b")
        {
            b = atof(argv[index + 1]);
            std::cout << ">>>> interval b = " << b << '\n';
        }
    }

    double mesh_size = (b - a) / N, err_norm = 0.;
    std::vector<double> sol_true(N + 1), sol_num(N + 1), rhs_b(N + 1, 0.);
    std::vector<double> grid_x(N + 1), grid_err(N + 1);

    rhs_b[0] = 1.;

    for (size_t index = 0; index < grid_x.size(); ++index)
    {
        grid_x[index] = a + index * mesh_size;
    }

    function_true(sol_true, grid_x);

    std::vector<double> mat_a_diag(N + 1, 1.), mat_a_down_diag(N, -1.);
    for (size_t index = 1; index < mat_a_diag.size(); ++index)
    {
        mat_a_diag[index] += mesh_size;
    }

    backward_euler_sol(sol_num, mat_a_diag, mat_a_down_diag, rhs_b);

    // grid_err = |sol_num - sol_true|
    for (size_t index = 0; index < grid_err.size(); ++index)
    {
        grid_err[index] = fabs(sol_num[index] - sol_true[index]);
        err_norm += grid_err[index] * grid_err[index];
    }
    std::cout << "numerical solution error: " << err_norm << '\n';
}

/*
 * diag: a0, a1, ..., aN
 * down diag: b0, b1, ..., bN-1
 * rhs: rhs0, rhs1, ..., rhsN
 *     u0 = rhs0 / a0
 *     u1 = rhs1 - b0 u0 / a1
 *     u2 = rhs2 - b1 u1 / a2
 *     ...
 *     uN = rhsN - bN-1 uN-1 / aN
 */
void backward_euler_sol(std::vector<double> &sol,
                        const std::vector<double> &a,
                        const std::vector<double> &b,
                        const std::vector<double> &rhs)
{
    sol[0] = rhs[0] / a[0];
    for (size_t index = 1; index < rhs.size(); ++index)
    {
        sol[index] = (rhs[index] - b[index - 1] * sol[index - 1]) / a[index];
    }
}

/*
 * true function
 *     u(x) = exp(-x)
 */
void function_true(std::vector<double> &sol,
                   const std::vector<double> &x)
{
    for (size_t index = 0; index < x.size(); ++index)
    {
        sol[index] = exp(-x[index]);
    }
}
