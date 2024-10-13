#include "../include/ex_impl.hpp"

typedef struct
{
    /* data */
    int n, nnz;
    std::vector<int> row_idx; // row indices
    std::vector<int> row_ptr; // row pointer
    std::vector<int> col_idx; // column indices
    std::vector<double> val;  // non-zero values
} CSRMat;

typedef struct
{
    /* data */
    int m, n, nnz;
    std::vector<int> row_idx;
    std::vector<int> col_idx;
    std::vector<double> val;
} COOMat;

void COO2CSR(CSRMat &mat_csr, const COOMat &mat_coo);

void GaussianEliminationPivot(COOMat &mat /*matrix data*/,
                              std::vector<double> &rhs /*rhs data*/,
                              std::vector<double> &sol /*numerical solution data*/);

void ex5_10(void)
{
    int m = 0, n = 0, nnz = 0;

    // rhs
    std::ifstream fp;
    fp.open("../input/x.vec");
    assert(fp);

    fp >> n;
    double *rhs_b = nullptr;
    rhs_b = new double[n];
    assert(rhs_b);

    for (int index = 0; index < n; ++index)
    {
        fp >> rhs_b[index];
    }
    std::cout << "size of vector: " << n << '\n';

#if 0 // check rhs data
    for (int index = 0; index < n; ++index)
    {
        std::cout << rhs_b[index] << '\n';
    }
#endif

    fp.close();

    // matrix
    fp.open("../input/a.mat");
    assert(fp);

    std::string buffer;

    // skip line start with '#' and blank line
    while (std::getline(fp, buffer))
    {
        if (buffer.empty() ||
            buffer[0] == '#')
        {
            continue;
        }

        std::istringstream line_size(buffer);
        if (line_size >> m >> n >> nnz)
        {
            break;
        }
    }

    std::cout << "size of matrix: m = " << m << ", n = " << n << ", nnz = " << nnz << '\n';

    int *row_idx = nullptr, *col_idx = nullptr;
    double *val = nullptr;
    row_idx = new int[nnz];
    col_idx = new int[nnz];
    val = new double[nnz];
    assert(row_idx && col_idx && val);

    for (int index = 0; index < nnz; ++index)
    {
        fp >> row_idx[index] >> col_idx[index] >> val[index];
    }

#if 0 // check matrix data
    for (int index = 0; index < nnz; ++index)
    {
        std::cout << row_idx[index] << '\t' << col_idx[index] << '\t' << val[index] << '\n';
    }
#endif

    fp.close();

#if 1
    // reorder coo data
    /*
     * step 1: ascending order with row_idx
     */
    int tmp_int = 0;
    double tmp_double = 0.;
    for (int index_i = 0; index_i < nnz - 1; ++index_i)
    {
        for (int index_j = index_i + 1; index_j < nnz; ++index_j)
        {
            if (row_idx[index_j] < row_idx[index_i])
            {
                // row_idx
                tmp_int = row_idx[index_i];
                row_idx[index_i] = row_idx[index_j];
                row_idx[index_j] = tmp_int;

                // col_idx
                tmp_int = col_idx[index_i];
                col_idx[index_i] = col_idx[index_j];
                col_idx[index_j] = tmp_int;

                // val
                tmp_double = val[index_i];
                val[index_i] = val[index_j];
                val[index_j] = tmp_double;
            }
        }
    }

    /*
     * step 2: ascending order with col_idx(same row_idx)
     */
    for (int index_i = 0; index_i < nnz - 1; ++index_i)
    {
        for (int index_j = index_i + 1; index_j < nnz; ++index_j)
        {
            if (row_idx[index_i] == row_idx[index_j])
            {
                if (col_idx[index_j] < col_idx[index_i])
                {
                    // row
                    tmp_int = row_idx[index_i];
                    row_idx[index_i] = row_idx[index_j];
                    row_idx[index_j] = tmp_int;

                    // col_idx
                    tmp_int = col_idx[index_i];
                    col_idx[index_i] = col_idx[index_j];
                    col_idx[index_j] = tmp_int;

                    // val
                    tmp_double = val[index_i];
                    val[index_i] = val[index_j];
                    val[index_j] = tmp_double;
                }
            }
        }
    }
#endif

#if 0
    // tuple
    std::vector<std::tuple<int, int, double>> combined;
    for (int index = 0; index < nnz; ++index)
    {
        combined.emplace_back(row_idx[index], col_idx[index], val[index]);
    }

    // reordering
    /*
     * step 1: row_idx[] with ascending order
     * step 2: col_idx[] with ascending order
     */
    std::sort(combined.begin(), combined.end(), [](const auto &a, const auto &b)
              { return std::tie(std::get<0>(a), std::get<1>(a)) < std::tie(std::get<0>(b), std::get<1>(b)); });

    // reassign row_idx[], col_idx[], val[]
    for (int index = 0; index < nnz; ++index)
    {
        row_idx[index] = std::get<0>(combined[index]);
        col_idx[index] = std::get<1>(combined[index]);
        val[index] = std::get<2>(combined[index]);
    }
#endif

    // coo matrix
    COOMat linsys_mat_coo;
    linsys_mat_coo.m = m;
    linsys_mat_coo.n = n;
    linsys_mat_coo.nnz = nnz;
    linsys_mat_coo.row_idx.assign(row_idx, row_idx + nnz);
    linsys_mat_coo.col_idx.assign(col_idx, col_idx + nnz);
    linsys_mat_coo.val.assign(val, val + nnz);

#if 0 // check data
    std::cout << ">>>> coo matrix reordering\n";
    std::cout << linsys_mat_coo.m << '\t' << linsys_mat_coo.n << '\t' << linsys_mat_coo.nnz << '\n';
    for (int index = 0; index < nnz; ++index)
    {
        std::cout << linsys_mat_coo.row_idx[index] << '\t'
                  << linsys_mat_coo.col_idx[index] << '\t'
                  << linsys_mat_coo.val[index] << '\n';
    }
    std::cout << ">>>> end coo matrix reordering\n";
#endif

    // std::vector
    std::vector<double> linsys_b(rhs_b, rhs_b + n);
    std::vector<double> linsys_sol(n); // numerical solution

    CSRMat linsys_mat_csr;
    COO2CSR(linsys_mat_csr, linsys_mat_coo);

#if 0 // check csr data
    std::cout << ">>>> csr matrix data:\n";
    std::cout << linsys_mat_csr.n << '\t' << linsys_mat_csr.nnz << '\n';
    for (int index = 0; index < linsys_mat_csr.n; ++index)
    {
        std::cout << linsys_mat_csr.row_idx[index] << '\n';
    }
    for (int index = 0; index < linsys_mat_csr.n + 1; ++index)
    {
        std::cout << linsys_mat_csr.row_ptr[index] << '\n';
    }
    for (int index = 0; index < linsys_mat_csr.nnz; ++index)
    {
        std::cout << linsys_mat_csr.col_idx[index] << '\n';
    }
    for (int index = 0; index < linsys_mat_csr.nnz; ++index)
    {
        std::cout << linsys_mat_csr.val[index] << '\n';
    }
    std::cout << ">>>> end csr matrix data\n";
#endif

    // gaussian elimination
    GaussianEliminationPivot(linsys_mat_coo, linsys_b, linsys_sol);
#if 1 // check numerical solution data
    std::cout << ">>>> numerical solution:\n";
    std::cout << linsys_sol.size() << '\n';
    for (int index = 0; index < n; ++index)
    {
        std::cout << linsys_sol[index] << '\n';
    }
    std::cout << ">>>> end numerical solution\n";
#endif

    // free memory
    delete[] rhs_b;
    delete[] row_idx;
    delete[] col_idx;
    delete[] val;
}

void COO2CSR(CSRMat &mat_csr, const COOMat &mat_coo)
{
    int n = mat_coo.n, nnz = mat_coo.nnz;
    mat_csr.n = n;
    mat_csr.nnz = nnz;

    mat_csr.row_idx.resize(n, 0);
    std::iota(mat_csr.row_idx.begin(), mat_csr.row_idx.end(), 0);

    mat_csr.row_ptr.resize(n + 1, 0);

    // nnz each row
    for (int index = 0; index < nnz; ++index)
    {
        ++mat_csr.row_ptr[mat_coo.row_idx[index] + 1];
    }

    // row_ptr
    for (int index = 0; index < n; ++index)
    {
        mat_csr.row_ptr[index + 1] += mat_csr.row_ptr[index];
    }

    // col_idx and val
    mat_csr.col_idx.resize(nnz, 0);
    mat_csr.val.resize(nnz, 0);

    // updating col_idx[], val[]
    for (int index = 0; index < nnz; ++index)
    {
        int row = mat_coo.row_idx[index]; // current row
        int dst_idx = mat_csr.row_ptr[row];

        mat_csr.col_idx[dst_idx] = mat_coo.col_idx[index];
        mat_csr.val[dst_idx] = mat_coo.val[index];

        ++mat_csr.row_ptr[row];
    }

    // reseting row_ptr
    for (int index = n; index > 0; --index)
    {
        mat_csr.row_ptr[index] = mat_csr.row_ptr[index - 1];
    }
    mat_csr.row_ptr[0] = 0;
}

void GaussianEliminationPivot(COOMat &mat,
                              std::vector<double> &rhs,
                              std::vector<double> &sol)
{
    int m = mat.m, nnz = mat.nnz;

    for (int index = 0; index < m - 1; ++index)
    {
        int pivot_row = index;
        double max_val = 0.;
        for (int index_i = index; index_i < m; ++index_i)
        {
            for (int index_k = 0; index_k < nnz; ++index_k)
            {
                if (mat.row_idx[index_k] == index_i && mat.col_idx[index_k] == index)
                {
                    if (fabs(mat.val[index_k]) > max_val)
                    {
                        max_val = fabs(mat.val[index_k]);
                        pivot_row = index_i;
                    }
                }
            }
        }
        // assert(max_val > 0.); // non-singular matrix
        if (max_val == 0.0)
        {
            throw std::runtime_error("Matrix is singular or nearly singular.");
        }

        // exchange row[index] and row[pivot_row]
        if (pivot_row != index)
        {
            // matrix
            for (int index_k = 0; index_k < nnz; ++index_k)
            {
                if (mat.row_idx[index_k] == index)
                {
                    mat.row_idx[index_k] = pivot_row;
                }
                else if (mat.row_idx[index_k] == pivot_row)
                {
                    mat.row_idx[index_k] = index;
                }
            }

            // rhs data
            double tmp = 0.;
            tmp = rhs[pivot_row];
            rhs[pivot_row] = rhs[index];
            rhs[index] = tmp;
        }

        // elimination
        for (int index_i = index + 1; index_i < m; ++index_i)
        {
            double scale = 0.;
            for (int index_k = 0; index_k < nnz; ++index_k)
            {
                if (mat.row_idx[index_k] == index_i && mat.col_idx[index_k] == index)
                {
                    scale = mat.val[index_k] / max_val;
                    break;
                }
            }

            if (scale != 0.)
            {
                // matrix data
                for (int index_k = 0; index_k < nnz; ++index_k)
                {
                    if (mat.row_idx[index_k] == index_i)
                    {
                        for (int index_j = 0; index_j < nnz; ++index_j)
                        {
                            if (mat.row_idx[index_j] == index && mat.col_idx[index_j] == mat.col_idx[index_k])
                            {
                                mat.val[index_k] -= scale * mat.val[index_j];
                            }
                        }
                    }
                }

                // rhs data
                rhs[index_i] -= scale * rhs[index];
            }
        }
    }

    // updating solution
    for (int index = m - 1; index >= 0; --index)
    {
        double sum = rhs[index];
        for (int index_k = 0; index_k < nnz; ++index_k)
        {
            if (mat.row_idx[index_k] == index && mat.col_idx[index_k] > index)
            {
                sum -= mat.val[index_k] * sol[mat.col_idx[index_k]];
            }
        }

        double pivot_val = 0.;
        for (int index_k = 0; index_k < nnz; ++index_k)
        {
            if (mat.row_idx[index_k] == index && mat.col_idx[index_k] == index)
            {
                pivot_val = mat.val[index_k];
            }
        }
        sol[index] = sum / pivot_val;
    }
}

void ex5_4(void)
{
    std::ifstream fp;
    fp.open("../input/x.vec");
    assert(fp);

    int size = 0;
    fp >> size;

    double *x = nullptr;
    x = new double[size];
    assert(x);

    for (int index = 0; index < size; ++index)
    {
        fp >> x[index];
    }

    fp.close();

    for (int index = 0; index < size; ++index)
    {
        std::cout << x[index] << '\n';
    }

    double x_bar = 0., sigma = 0.;
    for (int index = 0; index < size; ++index)
    {
        x_bar += x[index];
    }
    x_bar /= size;
    std::cout << "mean is " << x_bar << '\n';

    for (int index = 0; index < size; ++index)
    {
        sigma += (x[index] - x_bar) * (x[index] - x_bar);
    }
    sigma /= size - 1;
    sigma = sqrt(sigma);
    std::cout << "standard deviation is " << sigma << '\n';

    // free memory
    delete[] x;
}
