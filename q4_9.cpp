#include <iostream>
#include <vector>
#include <numeric>
#include <stdexcept>

using namespace std;

    bool check_is_9x9(vector<vector<int>>& vec){
        if(vec.size()!=9){
            cout<<"the shape is wrong."<<endl;
            return false;
        }
        for(auto& i: vec){
            if(i.size()!=9){
                return false;
            }
        
        }
        cout<<"the shape is right."<<endl;
        return true;
    }

    void print_row2d(const vector<vector<int>>& a){
        if (a.empty()) return;
        cout<<"this is printed by rows"<<endl;
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
        cout<<"this is printed by columns"<<endl;
        int i = static_cast<int>(a.size());
        int j = static_cast<int>(a[0].size());
        for (int c = 1; c <= j; ++c){
            for (int r = 1; r <= i; ++r){
                cout << a[r-1][c-1] << (r == i ? '\n' : ' ');
            }
        }
    }

    void print_3x32d(const vector<vector<int>>& a){
        if (a.empty()) return;
        cout<<"this is printed by 3x3"<<endl;
        for(int grid_rows =0;grid_rows<3;++grid_rows){
            for(size_t grid_columns=0; grid_columns<3;++grid_columns){
                cout << "Block (" << grid_rows << "," << grid_columns << "):"<<endl;
                for(size_t small_rows=0;small_rows<3;++small_rows){
                    for(size_t small_columns=0;small_columns<3;++small_columns){
                        int really_r=small_rows+3*grid_rows;
                        int really_c=small_columns+3*grid_columns;
                        if(small_columns==2){
                            cout<<a[really_r][really_c]<<endl;
                        }
                        else{
                            cout<<a[really_r][really_c]<<" ";
                        }
                    }
                    
                }
                cout<<endl;
            }
        }
    }

    void check_rows(vector<vector<int>>& a){
        if (a.empty()) return;
        
        bool check=true;
        int i = static_cast<int>(a.size());
        int j = static_cast<int>(a[0].size());
        for (int r = 1; r <= i; ++r){
            int sum = 0;
            for (int c = 1; c <= j; ++c){
                
                sum += a[r-1][c-1];
                
            }
            if(sum!=45){check=false;}
        }    
        if(check==true){
            cout<<"the sum of rows is 45."<<endl;
        }
        else{cout<<"the sum of rows is not 45."<<endl;}
    }

    void check_columns(vector<vector<int>>& a){
        if (a.empty()) return;
        
        bool check=true;
        int i = static_cast<int>(a.size());
        int j = static_cast<int>(a[0].size());
        for (int c = 1; c <= j; ++c){
            int sum = 0;
            for (int r = 1; r <= i; ++r){
                
                sum += a[r-1][c-1];
                
            }
            if(sum!=45){check=false;}
        }    
        if(check==true){
            cout<<"the sum of columns is 45."<<endl;
        }
        else{cout<<"the sum of columns is not 45."<<endl;}
    }

    void check_3x3(vector<vector<int>>& a){
        if (a.empty()) return;
        
        bool check=true;
        for(int grid_rows =0;grid_rows<3;++grid_rows){
            for(size_t grid_columns=0; grid_columns<3;++grid_columns){
                int sum = 0;
                for(size_t small_rows=0;small_rows<3;++small_rows){
                    
                    for(size_t small_columns=0;small_columns<3;++small_columns){
                        int really_r=small_rows+3*grid_rows;
                        int really_c=small_columns+3*grid_columns;
                        sum += a[really_r][really_c];
                    }
                    
                }
                if(sum!=45){check=false;}
                cout<<endl;
            }
        }
        if(check==true){
            cout<<"the sum of 3x3 is 45."<<endl;
        }
        else{cout<<"the sum of 3x3 is not 45."<<endl;}
    }

    int main() {
        vector<vector<int>> sudoku = {
            {8,9,5,7,4,1,6,2,3},
            {2,4,3,9,5,6,8,1,7},
            {7,6,1,8,2,3,4,9,5},
            {9,3,4,6,7,5,1,8,2},
            {6,1,7,2,9,8,5,3,4},
            {5,8,2,3,1,4,9,7,6},
            {3,5,9,1,6,2,7,4,8},
            {1,2,6,4,8,7,3,5,9},
            {4,7,8,5,3,9,2,6,1}
        };
        check_is_9x9(sudoku);
        print_row2d(sudoku);
        print_column2d(sudoku);
        print_3x32d(sudoku);
        check_3x3(sudoku);
        check_rows(sudoku);
        check_columns(sudoku);

        system("pause");
        return 0;

    }