#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
/*
Gen AI let me understand the Sieve Method
*/
using namespace std;

vector<int> sieve_primes(int n) {
    vector<int> primes;
    if (n <= 2) return primes;

    vector<bool> is_prime(n, true);
    is_prime[0] = false;
    is_prime[1] = false;

    primes.reserve(80000); 
    primes.push_back(2);    
/*
i = 3; i += 2：偶数（除了 2）一定不是质数，所以只枚举奇数。

i * 1LL * i < n：用 1LL 把乘法提升到 64 位，避免当 i*i 接近 32 位上限时溢出。等价于“i^2 < n”，因为当 i^2 >= n 时，再往后的倍数起点也越界了。

if (is_prime[i])：只有当 i 仍被认为是质数时，才去划掉它的倍数；否则说明它已经被更小的质数处理过了。

j = i * i：从 i^2 开始划。因为 < i^2 的倍数（比如 i*3, i*5 ...）都已经在更小的质数（如 3、5）那一轮被划过了，避免重复工作。

j += 2 * i：只跳到奇数倍（i*(2k+1)），跳过偶数倍（那些本来就是偶数，早就排除了），进一步加速。

*/
    for (size_t i = 3; i * 1LL * i < n; i += 2) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += 2 * i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 3; i < n; i += 2) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

int main() {
    const int N = 1000000;
    auto primes = sieve_primes(N);
    cout << "count = " << primes.size() << "\n";
    if (!primes.empty()) {
        cout << "first = " << primes.front()<< ", last = "  << primes.back()  << endl;
    }
    system("pause");
    return 0;
}