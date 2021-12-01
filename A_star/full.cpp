#include <bits/stdc++.h>
using namespace std;

typedef vector<vector <int> > Matrix;
typedef pair<int, int> position;

struct State {
    int f;
    int h;
    Matrix matrix;
};

struct comparator {
    bool operator()(State const& s1, State const& s2)
    {
        if(s1.f == s2.f) return s1.h > s2.h;
        return s1.f > s2.f;
    }
};



void print_matrix(Matrix matrix)
{
    cout << endl;
    for(int i=0; i<matrix.size(); i++) {
        for(int j=0; j<matrix.size(); j++) {
            if(matrix.at(i).at(j)) cout << matrix.at(i).at(j) << " ";
            else cout << "* ";
        }
        cout << endl;
    }cout <<"----------------------------------"<<endl;

}


void swap_matrix_elm(Matrix *matrix, int i1, int r1, int i2, int r2) {
    int temp = matrix -> at(i1).at(r1);
    matrix -> at(i1).at(r1) = matrix -> at(i2).at(r2) ;
    matrix -> at(i2).at(r2) = temp;
}


Matrix copyMatrix(vector<vector <int> > matrix)
{
    Matrix new_mat;

    for(int i=0; i<matrix.size(); i++) {
        vector<int> v1;
        v1.reserve(matrix.size());
        for(int j=0; j<matrix.size(); j++) {
            v1.push_back(matrix.at(i).at(j));
        }new_mat.push_back(v1);
    }
    return new_mat;
}


Matrix get_matrix(int grid_size) {
    Matrix matrix;
    int n;
    cout << "Enter initial board layout:" << endl;
    for (int i = 0; i < grid_size; i++) {
        vector<int> v1;
        v1.reserve(grid_size);
        for (int j = 0; j < grid_size; j++) {
            cin >> n;
            v1.push_back(n);
        }matrix.push_back(v1);
    }
    return matrix;
}


Matrix get_goal_matrix(int grid_size)
{
    Matrix matrix;
    int val = 0;

    for(int i=0; i<grid_size; i++) {
        vector<int> v1;
        v1.reserve(matrix.size());
        for(int j=0; j<grid_size; j++)
            v1.push_back(++val);
        matrix.push_back(v1);
    }
    matrix.at(grid_size-1).at(grid_size-1) = 0;
    return matrix;
}


int get_inversions(Matrix matrix) {
    int k = matrix.size();
    int inv = 0, size = k*k - 1;
    vector<int> list;

    for(int i=0; i<k; i++)
        for(int j=0; j<k; j++)
            if(matrix.at(i).at(j))
                list.push_back(matrix.at(i).at(j));

    for(int i=0; i<size; i++)
        for(int j=i+1; j<size; j++)
            if(list.at(i)> list.at(j)) inv++;

    return inv;
}


bool is_solvable(Matrix matrix) {
    int k = matrix.size();
    int inv = get_inversions(matrix);
    //odd grid_size e.g. 3
    if(k&1) {
        if(!(inv&1)) return true; //if inv is even
        else return false; //if inv is odd
    }
        //even grid_size e.g. 4
    else {
        int blank_r = -1;
        for(int i=0; i<k; i++)
            for(int j=0; j<k; j++)
                if(!matrix.at(i).at(j)) {
                    blank_r = i;
                    break;
                }
        if((blank_r&1 && !(inv&1)) || (!(blank_r&1) && inv&1))
            return true;
        else return false;
    }
}

pair<int, int> get_blank_pos(Matrix matrix) {
    for(int i=0; i<matrix.size(); i++)
        for(int j=0; j<matrix.size(); j++)
            if (!matrix.at(i).at(j)) return make_pair(i, j);

    return make_pair(-1, -1);
}

vector< Matrix > get_neighbours(Matrix matrix) {
    vector< Matrix > neighbours;
    pair<int, int> blank_pos = get_blank_pos(matrix);

    if(blank_pos.first != 0) { //can move UP
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first - 1, blank_pos.second);
        neighbours.push_back(m);
    }
    if(blank_pos.first != matrix.size() - 1) { //can move DOWN
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first + 1, blank_pos.second);
        neighbours.push_back(m);
    }
    if(blank_pos.second != 0) { //can move LEFT
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first, blank_pos.second - 1);
        neighbours.push_back(m);
    }
    if(blank_pos.second != matrix.size() - 1) { //can move RIGHT
        Matrix m = copyMatrix(matrix);
        swap_matrix_elm(&m, blank_pos.first, blank_pos.second, blank_pos.first, blank_pos.second + 1);
        neighbours.push_back(m);
    }

    return neighbours;
}



int hamming_distance(Matrix matrix, Matrix goal_mat) {
    int h = 0, k = matrix.size();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            if (matrix.at(i).at(j) != goal_mat.at(i).at(j) && goal_mat.at(i).at(j))
                h++;
        }
    return h;
}


int manhattan_distance(Matrix matrix, Matrix goal_mat) {
    int man = 0, k = matrix.size();
    map<int, position> position_matrix;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            position_matrix[matrix.at(i).at(j)] = make_pair(i, j);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            if (matrix.at(i).at(j) != goal_mat.at(i).at(j) && goal_mat.at(i).at(j)) {
                position pos = position_matrix[goal_mat.at(i).at(j)];
                man += abs(pos.first - i) + abs(pos.second - j);
            }

    return man;
}


bool correct_row(int val, int row, int k) {
    int bound = k * row;
    return val > bound && val <= (bound + k);
}


bool correct_col(int val, int col, int k) {
    return (val % k == col + 1) && val;
}


int linear_conflict(Matrix matrix, Matrix goal_mat) {
    int conflicts = 0, k = matrix.size();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            //row conflicts
            if (correct_row(matrix.at(i).at(j), i, k)) {
                for (int c = j + 1; c < k; c++)
                    if (matrix.at(i).at(j) > matrix.at(i).at(c) && correct_row(matrix.at(i).at(c), i, k)) {
                        conflicts++;
                        //cout << "pairs: " << matrix.at(i).at(j) << "," << matrix.at(i).at(c) << endl;
                    }
            }

            //column conflicts
            if (correct_col(matrix.at(j).at(i), i, k)) {
                for (int c = j + 1; c < k; c++)
                    if (matrix.at(j).at(i) > matrix.at(c).at(i) && correct_col(matrix.at(c).at(i), i, k)) {
                        conflicts++;
                        //cout << "pairs: " << matrix.at(j).at(i) << "," << matrix.at(c).at(i) << endl;
                    }
            }
        }

    return conflicts * 2 + manhattan_distance(matrix, std::move(goal_mat));
}


int get_h(const Matrix& matrix, const Matrix& goal_mat, int h) {
    if(h == 0) return hamming_distance(matrix, goal_mat);
    else if(h == 1) return manhattan_distance(matrix, goal_mat);
    else return linear_conflict(matrix, goal_mat);
}


typedef map< Matrix, Matrix > matrix_par;
void print_path(matrix_par parents, Matrix curr, const Matrix& start, int g) {
    g++;
    vector< Matrix > path;
    while (g--) {
        path.push_back(curr);
        curr = parents[curr];
    }
    for(int i=path.size()-1; i>=0; i--)
        print_matrix(path.at(i));
}


struct Gscore{
    int g = INT_MAX;
};

void solve(const Matrix& matrix, const Matrix& goal_matrix, int h_type) {
    map< Matrix, char> closed_list;
    matrix_par parents;
    map< Matrix, Gscore> closed_list_gscores;
    priority_queue<State, vector<State>, comparator > open_list;
    int explored = 0, expanded = 0;

    State state1;
    state1.h = get_h(matrix, goal_matrix, h_type);
    state1.f = state1.h;
    state1.matrix = matrix;

    open_list.push(state1);
    closed_list_gscores[state1.matrix].g = 0;

    while (!open_list.empty()) {
        State state = open_list.top();
        if(!state.h) { //found goal
            print_path(parents, goal_matrix, state1.matrix, state.f - state.h);
            cout << "cost = " << state.f - state.h << endl;
            cout << "explored: " << explored << ", expanded: " << expanded << endl;

            return;
        }
        open_list.pop(); expanded++;
        int current_g = state.f - state.h;
        closed_list[state.matrix] = 'y';
        closed_list_gscores[state.matrix].g = current_g;


        vector< Matrix > neighbours = get_neighbours(state.matrix);
        current_g++;
        for(const Matrix& neighbour: neighbours) {
            if(closed_list_gscores[neighbour].g > current_g) {
                State s;
                s.h = get_h(neighbour, goal_matrix, h_type);
                s.f = current_g + s.h;
                s.matrix = neighbour;
                open_list.push(s);
                closed_list_gscores[s.matrix].g = current_g;
                closed_list[s.matrix] = 'y';
                parents[s.matrix] = state.matrix;
                explored++;
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
    if(is_solvable(matrix)) {
        cout << "puzzle is solvable\n";
        cout<< "================solving using hamming:===================\n";
        solve(matrix, get_goal_matrix(grid_size), 0);
        cout<< "================solving using manhattan:===================\n";
        solve(matrix, get_goal_matrix(grid_size), 1);
        cout<< "================solving using linear conflict:===================\n";
        solve(matrix, get_goal_matrix(grid_size), 2);
    }else cout << "puzzle is NOT solvable!\n";

    return 0;
}
