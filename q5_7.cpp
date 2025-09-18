#include <iostream>
#include <cmath>     
#include <limits>    

using namespace std;

int main() {
    cout << "Enter point A (xA yA): ";
    double ax, ay;
    if (!(cin >> ax >> ay)) {
        cerr << "Input error for point A."<<endl;
        return 1;
    }

    cout << "Enter point B (xB yB): ";
    double bx, by;
    if (!(cin >> bx >> by)) {
        cerr << "Input error for point B."<<endl;
        return 1;
    }


    const double dx = bx - ax;
    const double dy = by - ay;

    double distance=sqrt(pow(bx-ax,2)+pow(by-ay,2));
    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "Distance(A, B) = " << distance <<endl;

    system("pause");
    return 0;
}
