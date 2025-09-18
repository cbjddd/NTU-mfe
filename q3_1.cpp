#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double function_calculation(double x){
    double result;
    result = sin(x)*sin(x)+exp(-x*x)+x*x*x*log(x+1);
    return result;
}

int main() {
    for (double x = 0.0; x<=1.0; x += 0.1){
        cout << "x=" <<fixed << setprecision(1) << x<<endl;
        cout << "f(x)=" <<fixed << setprecision(5) << function_calculation (x)<<endl;
    }
    system("pause");
    return 0;
}