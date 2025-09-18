#include <iostream>
#include <random>
#include <cmath>
#include <vector>
using namespace std;

seed_seq seed2{90128u, 43021u, 89427u}; // 多个32位种子更充分初始化状态
mt19937 gen_det(seed2);                 // 32位 Mersenne Twister                       
uniform_int_distribution<int> dist(1, 2000); 



int main(){
    const long long N=1'000'000;
    vector<int> random_int(N);
    long long count;
    for(long long i=0;i<random_int.size();++i){
        random_int[i]=dist(gen_det);
        if (random_int[i]>=500&&random_int[i]<=1000&& random_int[i]%163==0){
            ++count;
            cout<<random_int[i]<<endl;
        }
        
    }
    cout<<endl;

    system("pause");
    return 0;

}