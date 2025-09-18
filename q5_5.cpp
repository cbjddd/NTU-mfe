#include <algorithm>
#include <iostream>
#include <numeric> 
#include <string>
#include <vector>

using namespace std;

bool is_strictly_sorted_mannually(const vector<int>& v){
    if (v.size()<=1){return true;}
    bool check=true;
    for(size_t i=1;i<v.size();++i){
        if (! (v[i-1]<v[i])){
            check=false;
        }
    }
    return check;

}

bool is_strictly_sorted_STL(const vector<int>& v){
    if (v.size()<=1){return true;}
    bool check;
    auto it=adjacent_find(v.begin(), v.end(), [](int a,int b){return a >= b;});
    return check = (it == v.end());
}


void run_one(const vector<int>& v, const string& name, bool expected) {
    bool r1 = is_strictly_sorted_STL(v);
    bool r2 = is_strictly_sorted_mannually(v);
    cout << name << "  -> adjacent_find: " << (r1 ? "true " : "false")
         << " | all_of: " << (r2 ? "true " : "false")
         << " | expected: " << (expected ? "true" : "false") << endl;
}

int main(){
    run_one({},                 "empty",                true);
    run_one({42},               "single",               true);
    run_one({1,2,3,4,5},        "strictly increasing",  true);
    run_one({1,2,2,4,5},        "non-strict (equal)",   false);
    run_one({5,4,3,2,1},        "decreasing",           false);
    run_one({3,1,4,1,5},        "random order",         false);

    system("pause");
    return 0;
}

