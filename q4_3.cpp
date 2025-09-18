#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void bubble_sort(vector<double>& arr){
    const size_t i = arr.size();
    if (i<2) {return;}
    for (size_t n=0;n<i-1;++n){
        bool swapped = false;
        for(size_t m=0;m<i-n-1;++m){
            if (arr[m]>arr[m+1]){
                swap(arr[m],arr[m+1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

void test_bubble_sort(vector<double>& test_arr){
    bubble_sort(test_arr);
    bool has_mistake = false;
    for (size_t i=0;i+1<test_arr.size();++i){
        if(test_arr[i]>test_arr[i+1]){
            cout<<"There is a mistake at"<<i<<"and"<<i+1<<endl;
            has_mistake=true;
        }   
    }
    if (has_mistake==false){    cout<<"There is no mistake."<<endl;}

    for (size_t i=0;i<test_arr.size();++i){
        cout<<test_arr[i]<<"  ";
    }
    cout<<endl;
}

int main(){
    vector<double> a{3.1, -2.0, 7.5, 7.5, 0.0};
    vector<double> b{};                    
    vector<double> c{42.0};                
    vector<double> d{5,4,3,2,1};           
    vector<double> e{-1.2, -1.2, 0.0, 3.3}; 
    test_bubble_sort(a);
    test_bubble_sort(b);
    test_bubble_sort(c);
    test_bubble_sort(d);
    test_bubble_sort(e);

    system("pause");
    return 0;
}