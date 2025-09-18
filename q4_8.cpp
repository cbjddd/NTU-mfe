#include <iostream>
#include <vector>

using namespace std;

void print_vector_element(vector<int>& v){
    for (auto& element: v){
        cout<<element<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> vec(10);
    print_vector_element(vec);

    vec.push_back(314);
    vec.push_back(159);
    print_vector_element(vec);

    if (!vec.empty()){
        vec.pop_back();
        print_vector_element(vec);
    }

    vec.resize(20);
    print_vector_element(vec);

    system("pause");
    return 0;
}

