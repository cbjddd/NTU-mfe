#include <iostream>
#include <list>

using namespace std;

bool is_even(int a){
    if (a%2==0) {return true;}
    else {return false;}
}

int main(){
    list<int> L1;
    for (int i=0;i<10;++i){
        L1.push_back(i);
    }
    list<int> L2;
    for(int j=10;j<20;++j){
        L2.push_back(j);
    }

    L1.splice(L1.end(),L2);
    cout<<"size of L1 is "<<L1.size()<<endl;
    cout<<"size of L2 is "<<L2.size()<<endl;

    L1.remove_if(is_even);

    if (!L1.empty()){
        cout<<"first element of L1 is"<<L1.front()<<endl;
        cout<<"last element of L1 is"<<L1.back()<<endl;
    }
    else{
        cout<<"L1 is empty."<<endl;
    }
    for(int m : L1){
        cout<<" "<<m<<" ";
    }
    cout<<endl;
    system("pause");
    return 0;
}