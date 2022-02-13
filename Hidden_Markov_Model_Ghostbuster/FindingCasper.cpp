#include <bits/stdc++.h>
using namespace std;

class CasperMat{
    double **mat;
    int n, m, k;
    int casper_r, casper_c;
    int reading_count;
    public:
        CasperMat(int, int, int);
        ~CasperMat();

        void init_mat();
        void print_mat();

        bool withinRange(int, int);
        double get_transition_val(int, int, bool);
        double recalculate_elm(int, int);
        void recalculate_mat();

        void resensor_mat(int, int, bool);
        void normalize_mat();

        void startFindingCasper();
};

CasperMat::CasperMat(int n, int m, int k)
{
    this -> n = n;
    this -> m = m;
    this -> k = k;
    mat = new double*[n];
    for(int i=0; i<n; i++) {
        mat[i] = new double[m];
    }
    casper_r = -1;
    casper_c = -1;
    reading_count = 0;
}

CasperMat::~CasperMat()
{
    for(int i=0; i<n; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

void CasperMat::init_mat()
{
    int prob = n * m - k;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            mat[i][j] = 1.000/prob;

    int u, v;
    for(int i=0; i<k; i++) {
        cin >> u >> v;
        mat[u][v] = 0;
    }
}

void CasperMat::print_mat()
{
    cout << "\n=============Probability Update [Reading "<< reading_count <<"]===============\n";
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(!mat[i][j]) cout << "0.00000 ";
            else cout << mat[i][j] * 100.0000 << " ";
        }
        cout << endl;
    }
    cout << "==================================================================\n\n";
}


bool CasperMat::withinRange(int i, int j)
{
    return i>=0 && i<n && j>=0 && j<m;
}

double CasperMat::get_transition_val(int r, int c, bool is_edge)
{
    int cell_count;
    if(is_edge)
    {
        cell_count = 0;
        if(withinRange(r, c-1))
            if(mat[r][c-1]) cell_count++;

        if(withinRange(r, c+1))
            if(mat[r][c+1]) cell_count++;

        if(withinRange(r+1, c))
            if(mat[r+1][c]) cell_count++;

        if(withinRange(r-1, c))
            if(mat[r-1][c]) cell_count++;

//        cout << "cell_count(e): " << cell_count << endl;
//        cout << "val " << mat[r][c] << endl;
        return (mat[r][c]*0.90000)/cell_count;
    }
    else //corner
    {
        cell_count = 1;
        if(withinRange(r-1, c-1))
            if(mat[r-1][c-1]) cell_count++;

        if(withinRange(r-1, c+1))
            if(mat[r-1][c+1]) cell_count++;

        if(withinRange(r+1, c-1))
            if(mat[r+1][c-1]) cell_count++;

        if(withinRange(r+1, c+1))
            if(mat[r+1][c+1]) cell_count++;

//        cout << "cell_count: " << cell_count << endl;
//        cout << "val " << mat[r][c] << endl;
        return (mat[r][c]*0.10000)/cell_count;
    }
}

double CasperMat::recalculate_elm(int r, int c)
{
    //middle
    //double val = mat[r][c] * 0.10000;
    double val = get_transition_val(r, c, false);

    //top three
    int i = r - 1, j = c - 1;
    for(int k=0; k<3; k++, j++)
    {
        if(withinRange(i, j)){
            if(mat[i][j]) {
                val += get_transition_val(i, j, k==1);
//                cout << "1value gese " << i << " " << j << " for r,c " << r << c << endl;
            }
        }
    }

    //bottom three
    i = r + 1, j = c - 1;
    for(int k=0; k<3; k++, j++)
    {
        if(withinRange(i, j)){
            if(mat[i][j]) {
                val += get_transition_val(i, j, k==1);
//                cout << "2value gese " << i << " " << j << " for r,c " << r << c << endl;

            }
        }
    }

    //rest two
    if(withinRange(r, c-1)){
        if(mat[r][c-1]){
            val += get_transition_val(r, c-1, true);
//            cout << "3value gese " << r << " " << c-1 << " for r,c " << r << c << endl;

        }
    }
    if(withinRange(r, c+1)){
        if(mat[r][c+1]){
            val += get_transition_val(r, c+1, true);
//            cout << "4value gese " << r << " " << c+1 << " for r,c " << r << c << endl;

        }
    }

    return val;
}


void CasperMat::recalculate_mat()
{
    double temp_arr[n][m];
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
            temp_arr[i][j] = mat[i][j];
    }


    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
        if(mat[i][j]){
            temp_arr[i][j] = recalculate_elm(i, j);
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
            mat[i][j] = temp_arr[i][j];
    }
}


void CasperMat::resensor_mat(int r, int c, bool found)
{
    if(!withinRange(r,c)){
        cout << "input coordinates out of bounds!\n";
        return;
    }

    reading_count++;
    double inner_weight = 0.15000;
    double outer_weight = 0.85000;
    if(found) swap(inner_weight, outer_weight);

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(mat[i][j]) {
                if(i<=r+1 && i>=r-1 && j<=c+1 && j>=c-1)
                    mat[i][j] *= inner_weight;
                else
                    mat[i][j] *= outer_weight;
            }
        }
    }
}


void CasperMat::normalize_mat()
{
    //casper assumed to be in first cell
    casper_c = 0;
    casper_r = 0;
    double max_p = 0;

    double sum = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++){
            if(mat[i][j]) sum += mat[i][j];

            //cell with max prob.
            if(mat[i][j] > max_p)
            {
                max_p = mat[i][j];
                casper_r = i;
                casper_c = j;
            }
        }
    }

    //normalize
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++)
            if(mat[i][j]) mat[i][j] /= sum;
    }
}


void CasperMat::startFindingCasper()
{
    string comm;
    int r, c, val;
    print_mat();
    while(1)
    {
        cin >> comm;
        if(!comm.compare("R") || !comm.compare("r")){
            cin >> r >> c >> val;
            recalculate_mat();
            resensor_mat(r, c, val);
            normalize_mat();
            print_mat();
        }
        else if(!comm.compare("C") || !comm.compare("c"))
            cout << "\nCasper is most probably at cell [" << casper_r << ", " << casper_c << "]\n";
        else if(!comm.compare("Q") || !comm.compare("q"))
        {
            cout << "Bye Casper!\n";
            break;
        }
    }
}


int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    CasperMat caspermat(n, m, k);
    caspermat.init_mat();
    caspermat.startFindingCasper();
    return 0;
}
