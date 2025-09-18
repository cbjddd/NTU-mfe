#include <vector>
#include <tuple>
#include <iostream>
#include <cassert>
using namespace std;

std::tuple<bool, std::vector<double>> add_vectors(const std::vector<double>& vec1, const std::vector<double>& vec2){
    if(vec1.size()!= vec2.size()) {
        cout<<"The size of two vectors is not the same! Please check!"<<endl;
        return {false, {}};
    }
    vector<double> result(vec1.size());
    for (size_t i=0;i<vec1.size();++i){
        result[i]=vec1[i]+vec2[i];
    }
    return {true, move(result)};
}

void test_add_vector() {
    {
        vector<double> a{1,2,3}, b{10,20,30};
        auto [bool1, sum1] = add_vectors(a, b);
        cout << "case1 ok=" << boolalpha << bool1 << " sum=[";
        for (size_t i=0;i<sum1.size();++i)
            cout << sum1[i] << (i+1<sum1.size()? ", ":"");
        cout << "]"<<endl;
    }
    {
        vector<double> a{1,2,3}, c{1,2};
        auto [bool2, sum2] = add_vectors(a, c);
        cout << "case2 ok=" << boolalpha << bool2 << " (expect false)"<<endl;
    }
}