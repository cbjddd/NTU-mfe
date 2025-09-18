#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

static mt19937 rng{random_device{}() };  

vector<double> rand_vector(int n, double a = 0.0, double b = 1.0){
    if (n<=0){
        cout<<"sorry n must be positive!"<<endl;
        return {};
    }
    if(a>b) swap(a,b);

    uniform_real_distribution<double> dist(a, b);
    vector<double> v;
    v.resize(n);
    for (auto &x : v){
        x=dist(rng);
    }
    return v;
}

bool check_value(const vector<double>& v, double a, double b){
    vector<int> check_vector;
    check_vector.resize(v.size());
    if(a>b) swap(a,b);
    for (int i=0; i<v.size();++i){
        if(a<=v[i]&&b>=v[i]) check_vector[i]=1;
        else check_vector[i]=0;
    }
    for (const auto& x : check_vector) {
        if (x != 1) {
            return false;
        }
    }
    return true;
}


int main(){
    auto v1 = rand_vector(10);           
    auto v2 = rand_vector(8, -1.0, 1.0); 
    auto v3 = rand_vector(5, 10.0, 20.0);

    cout << "v1 in [0,1] : "   << check_value(v1, 0.0, 1.0)   << endl;
    cout << "v2 in [-1,1]: "   << check_value(v2, -1.0, 1.0)  << endl;
    cout << "v3 in [10,20]: "  << check_value(v3, 10.0, 20.0) << endl;

    auto print_elements = [](const vector<double>& v){
        
        for (size_t i = 0; i <v.size(); ++i)
            cout << fixed << setprecision(4) << v[i] << ' ';
        cout << endl;
    };

    print_elements(v1);
    print_elements(v2);
    print_elements(v3);

    system("pause");
    return 0;

}