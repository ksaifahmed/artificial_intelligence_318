#include "mat_utils.cpp"
#include "hueristics.cpp"


int main()
{
    int grid_size = 3;
    cout << "Enter grid size, k: ";
    cin >> grid_size;
    vector<vector <int> > matrix = get_matrix(grid_size);

    print_matrix(matrix);
    print_matrix(copyMatrix(matrix));
    print_matrix(get_goal_matrix(grid_size));
    cout << "h is " << linear_conflict(matrix, get_goal_matrix(grid_size));
    is_solvable(matrix);
    cout << get_inversions(matrix);
    cout << "\n\nhamming: " <<hamming_distance(matrix, get_goal_matrix(grid_size));




    return 0;
}