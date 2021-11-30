#include "mat_utils.cpp"
#include "hueristics.cpp"

typedef pair<int, Matrix > State;
void solve(const Matrix& matrix, const Matrix& goal_matrix, int h_type) {
    int g = 0;
    map< Matrix, char> closed_list;
    priority_queue<State, vector<State>, greater<State> > open_list;
    open_list.push(make_pair(g + get_h(matrix, goal_matrix, h_type), matrix));

    while (!open_list.empty()) {
        State state = open_list.top();
        int h = get_h(state.second, goal_matrix, h_type);
        if(!h) { //found goal
            cout << "\n\ngoal reached:\n";
            print_matrix(state.second);
            cout << "h = 0, g = " << g;
            return;
        }
        open_list.pop();
        print_matrix(state.second);
        cout << "h = " << h <<", g = " << g++ << endl << endl;
        closed_list[state.second] = 'y';

        vector< Matrix > neighbours = get_neighbours(state.second);
        for(const Matrix& neighbour: neighbours) {
            if(closed_list[neighbour] != 'y') {
                open_list.push(make_pair(g++ + get_h(neighbour, goal_matrix, h_type), neighbour));
            }
        }
    }
}





int main()
{
    int grid_size;
    cout << "Enter grid size, k: ";
    cin >> grid_size;
    Matrix matrix = get_matrix(grid_size);
    solve(matrix, get_goal_matrix(grid_size), 0);

//    print_matrix(matrix);
//    print_matrix(copyMatrix(matrix));
//    print_matrix(get_goal_matrix(grid_size));
//    cout << "h is " << linear_conflict(matrix, get_goal_matrix(grid_size));
//    is_solvable(matrix);
//    cout << get_inversions(matrix);
//    cout << "\n\nhamming: " <<hamming_distance(matrix, get_goal_matrix(grid_size));






//        pq.push(make_pair(10, 500));
//        pq.push(make_pair(20, 100));
//        pq.push(make_pair(15, 400));
//        pair<int, int> top = pq.top();
//        pq.pop();
//    top = pq.top();
//        cout << top.first << " " << top.second;


    return 0;
}