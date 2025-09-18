#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <set>
#include "zero_rate_curve.h"   
#include <algorithm>

using namespace std;


vector<int> intersection_stl(const set<int>& a, const set<int>& b) {
    vector<int> ans;
    set_intersection(a.begin(), a.end(),
                     b.begin(), b.end(),
                     back_inserter(ans));
    return ans;
}

vector<int> intersection_myself(const set<int>& a, const set<int>& b){
    vector<int> ans;
    for(int i : a){
        for(int j:b){
            if (i==j){
                ans.push_back(i);
                break;
            }
        }
    }
    return ans;
}

void print_set(const vector<int>& a){
    for(int x:a){
        cout<<x<<" ";
    }
    cout<<endl;
}


int main(){
    set<int> set1{1,2,3,4,5};
    set<int> set2{2,3,4,5,7};
    set<int> set3{3,8,9,7,6};

    auto a12 = intersection_stl(set1, set2);
    auto a13 = intersection_stl(set1, set3);
    auto a23 = intersection_stl(set2, set3);

    cout << "[Using STL]"<<endl;
    cout<<"1-2";
    print_set(a12);
    cout<<"1-3";
    print_set(a13);
    cout<<"2-3";
    print_set(a23);
    cout<<endl;

    cout << "[Using naive double-loop]"<<endl;
    auto b12 = intersection_myself(set1, set2);
    auto b13 = intersection_myself(set1, set3);
    auto b23 = intersection_myself(set2, set3);
    cout<<"1-2";
    print_set(b12);
    cout<<"1-3";
    print_set(b13);
    cout<<"2-3";
    print_set(b23);
    system("pause");
    return 0;
}