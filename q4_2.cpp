#include <iostream>
#include <vector>
using namespace std;

long long recursive_memoization(int n,int k, vector<vector<long long>>& memo){
    if (n == 0) return 1;
    if (n < 0 || k < 1) return 0;
    if (k == 1) return 1;
    long long& cell = memo[n][k];
    if (cell != -1) return cell;               
    cell = recursive_memoization(n, k - 1, memo) +recursive_memoization(n - k, k, memo);        
    return cell;
}

long long recursive(int n){
    if(n<0){
        return 0;
    }
    vector<vector<long long>> memo(n + 1, vector<long long>(n + 1, -1));
    long long i = recursive_memoization(n,n,memo);
    return i;
}

int main(){
    cout << "p(1) = " << recursive(1) <<endl;
    cout << "p(2) = " << recursive(2) <<endl;
    cout << "p(3) = " << recursive(3) <<endl;
    cout << "p(4) = " << recursive(4) <<endl;
    cout << "p(5) = " << recursive(5) <<endl;
    cout << "p(50) = " << recursive(50) <<endl;
    system("pause");
    return 0;
}