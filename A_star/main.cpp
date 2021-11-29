#include "mat_utils.cpp"
#include "hueristics.cpp"


int main()
{
    int grid_size;
    cout << "Enter grid size, k: ";
    cin >> grid_size;
    int ** matrix = get_matrix(grid_size);
    print_matrix(matrix, grid_size);
    print_matrix(copyMatrix(matrix, grid_size), grid_size);
    print_matrix(get_goal_matrix(grid_size), grid_size);

    cout << "h is " << linear_conflict(matrix, get_goal_matrix(grid_size), grid_size);
    is_solvable(matrix, grid_size);

    return 0;
}