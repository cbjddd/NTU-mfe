#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cassert>

using namespace std;

int gcd(int a, int b){
    if (a == 0) return b;
    if (b == 0) return a;
    if (a<0) a=abs(a);
    if (b<0) b=abs(b);
    while (b!=0){
        int r = a%b;
        a=b;
        b=r;
    }
    return a;
}

void test_gcd(){
    cout<<"find the gdc of 48 and 18"<<endl;
    if(gcd(48, 18)==6){cout<<"This function passes the test!"<<"The gcd of 48 and 18 is"<<gcd(48,18)<<endl;}
    cout<<"The gcd of of 0 and 5 is "<<gcd(0,5)<<endl;
    cout<<"The gcd of of 7 and 0 is "<<gcd(7,0)<<endl;
    cout<<"The gcd of of 1071 and 462 is "<<gcd(1071,462)<<endl;

}

int main(){
    test_gcd();

    system("pause");
    return 0;
}