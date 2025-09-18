#include <iostream>
#include <cmath>

using namespace std;

long long multiply_integers(int a, int b){
    return a*b;
}

bool same_parity(int a, int b) {
    return (abs(a)%2==abs(b)%2);
}

int main(){
    cout<<"question3_1 part1 test:"<<multiply_integers(9,9)<<endl;
    cout<<"question3_1 part1 test:"<<multiply_integers(100000000,293280989)<<endl;
    cout<<"question3_1 part2 test:"<<same_parity(5,7)<<endl;
    cout<<"question3_1 part2 test:"<<same_parity(2,222)<<endl;
    cout<<"question3_1 part2 test:"<<same_parity(5,152)<<endl;

    system("pause");
    return 0;
}