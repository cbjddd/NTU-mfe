#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <iterator> 

using namespace std;

seed_seq seed2{90128u, 43021u, 89427u}; // 多个32位种子更充分初始化状态
mt19937 gen_det(seed2);                 // 32位 Mersenne Twister

int main(){
    uniform_real_distribution<double> dis(0.0, 1.0);
    const long long size=100'000;
    vector<bool> random_bool(size);
    generate(random_bool.begin(),random_bool.end(),[&] {return dis(gen_det)>0.5;});

    vector<bool> check_lisk(15,true);
    auto it=search(random_bool.begin(),random_bool.end(),check_lisk.begin(),check_lisk.end());

    if (it!=random_bool.end()){
        long long position =static_cast<long long> (distance(random_bool.begin(),it));
        cout << "Found 15 consecutive trues starting at index " << position << endl;
    }
    else{
        cout << "We can't find 15 consecutive trues was found."<<endl;
    }
    
    system("pause");
    return 0;
}