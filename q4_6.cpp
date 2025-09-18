#include <iostream>
#include <vector>

using namespace std;

int find_location(const vector<int>& m, int i, int j, int r, int c) {
    if (i <= 0 || j <= 0) throw invalid_argument("both i and j need to be positive");
    long long expected = 1LL * i * j;
    if (static_cast<long long>(m.size()) != expected)
        throw invalid_argument("m.size() must be i*j");
    if (r < 1 || r > i || c < 1 || c > j)
        throw out_of_range("r or c is out of range (1-based)");

    return (r - 1) * j + (c - 1); 
}

void print_rows1d(const vector<int>& m, int i, int j){
    for (int r = 1; r <= i; ++r){
        for (int c = 1; c <= j; ++c){
            int idx = find_location(m, i, j, r, c);
            cout << m[idx] << (c == j ? '\n' : ' ');
        }
    }
}

void print_columns1d(const vector<int>& m, int i, int j){
    for (int c = 1; c <= j; ++c){
        for (int r = 1; r <= i; ++r){
            int idx = find_location(m, i, j, r, c);
            cout << m[idx] << (r == i ? '\n' : ' ');
        }
    }
}

void print_row2d(const vector<vector<int>>& a){
    if (a.empty()) return;
    int i = static_cast<int>(a.size());
    int j = static_cast<int>(a[0].size());
    for (int r = 1; r <= i; ++r){
        for (int c = 1; c <= j; ++c){
            cout << a[r-1][c-1] << (c == j ? '\n' : ' ');
        }
    }
}

void print_column2d(const vector<vector<int>>& a){
    if (a.empty()) return;
    int i = static_cast<int>(a.size());
    int j = static_cast<int>(a[0].size());
    for (int c = 1; c <= j; ++c){
        for (int r = 1; r <= i; ++r){
            cout << a[r-1][c-1] << (r == i ? '\n' : ' ');
        }
    }
}

int main(){
    vector<int> m = { 1,2,3,4, 5,6,7,8, 9,10,11,12 };

    cout << "1D by rows:\n";
    print_rows1d(m, 3, 4);


    cout << "1D by cols:\n";
    print_columns1d(m, 3, 4);

    vector<vector<int>> n = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    };

    cout << "2D by rows:\n";
    print_row2d(n);

    cout << "2D by cols:\n";
    print_column2d(n);
    system("pause");
    return 0;
}