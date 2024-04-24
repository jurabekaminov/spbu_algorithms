#include <vector>
#include <cassert>
#include <iostream>

typedef std::vector<bool> matrix_row;
typedef std::vector<matrix_row> matrix;

matrix transform(const matrix &adj)
{
    int cols = adj.size();
    assert(cols > 0);

    int rows = adj[0].size();
    assert(rows > 0);

    assert(rows == cols);

    int edge = 0;
    matrix incidence;

    for (int col = 0; col < cols; ++col)
    {
        for (int row = 0; row <= col; ++row)
        {
            if (adj[col][row])
            {
                incidence.push_back(matrix_row(cols, 0));
                incidence[edge][row] = incidence[edge][col] = 1;
                ++edge;
            }
        }
    }

    return incidence;
}
