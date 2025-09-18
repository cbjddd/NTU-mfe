#include <list>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

void replace_zero2one(list<int>& L){
    for(int& x:L){
        if (x==0){x=1;}
    }
}
void comparsion_list(list<int> L1,list<int> L2){
    if (L1.size()!=L2.size()){
        cout<<"The size of two lists is different."<<endl;
    }
    if (L1==L2){
        cout<<"The two lists are the same."<<endl;
    }

}
int main(){
    list<int> L1 = {0,0,1,3,0,5,0,6};
    replace_zero2one(L1);
    list<int> E1 = {1,1,1,3,1,5,1,6};
    comparsion_list(L1,E1);
    list<int> L2 = {0,0,0};
    replace_zero2one(L2);
    list<int> E2 = {1,1,1};
    comparsion_list(L2,E2);
    list<int> L3 = {2,4,-1,7};
    replace_zero2one(L3);
    list<int> E3 = {2,4,-1,7};
    comparsion_list(L3,E3);
    list<int> L4 = {};
    replace_zero2one(L4);
    list<int> E4 = {};
    comparsion_list(L4,E4);
    system("pause");
    return 0;
}