#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>

using namespace std;

int main(){
    ofstream outfile("squareroots.txt");
    if(!outfile){
        cerr<<"Error creating file!"<<endl;
        return 1;
    }
    outfile<<fixed<<setprecision(7);

    for(size_t i=1;i<=100;++i){
        double r = sqrt(static_cast<double>(i));
        outfile<<setw(3)<<i<<" "<<setw(15)<<r<<endl;
    }

    outfile.close();
    system("pause");
    return 0;
}