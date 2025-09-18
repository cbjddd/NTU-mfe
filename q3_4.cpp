/*
Gen AU: Use GPT help me solve the problem of calculating time period

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <numeric>
using namespace std;


void change_x(int x){
    x +=1;
    
}

void change_x_with_ref(int& x){
    x +=1;
      
}
static size_t sink = 0;

void value_copy(std::vector<int> v){
    
    sink += v.size(); //avoid being optimized
}

void value_copy_with_ref(const vector<int>& v) {
    sink += v.size();
}

int main() {
    int y = 10;
    change_x(y);               
    cout << "After change_x(y): y = " << y << endl;
    change_x_with_ref(y);      
    cout << "After change_x_with_ref(y): y = " << y << endl;

    const size_t N = 1'000'000;                  
    vector<int> big(N);
    std::iota(big.begin(), big.end(), 0);             

    const size_t R = 1000;

    using clock_t = chrono::high_resolution_clock;

    auto t1 = clock_t::now();
    for (size_t i = 0; i < R; ++i) value_copy(big);
    auto t2 = clock_t::now();

    auto t3 = clock_t::now();
    for (size_t i = 0; i < R; ++i) value_copy_with_ref(big);
    auto t4 = clock_t::now();

    auto ms_copy = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    auto ms_ref  = chrono::duration_cast<chrono::milliseconds>(t4 - t3).count();

    cout << "value_copy (by value)     : " << ms_copy << " ms"<<endl;
    cout << "value_copy_with_ref (by const&): " << ms_ref  << " ms"<<endl;
    if (ms_ref > 0)
        cout << "Speedup (copy / ref) ≈ " << fixed << setprecision(1)
             << (double)ms_copy / (double)ms_ref << "x"<<endl;

    system("pause");
    return 0;
}