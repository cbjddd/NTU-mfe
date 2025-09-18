#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

// round to 2 decimals
static inline double r2(double x) { return std::round(x * 100.0) / 100.0; }

// one allocation according to the scheme
vector<double> send_once(size_t n, double total, mt19937 &gen) {
    vector<double> a(n, 0.0);
    if (n == 0) return a;

    uniform_real_distribution<double> U(0.0, 1.0);
    double remain = r2(total);

    for (size_t i = 0; i + 1 < n; ++i) {
        size_t left = n - i;
        double upper = 2.0 * remain / static_cast<double>(left); // average * 2
        if (upper < 0.01) upper = 0.01;
        double x = 0.01 + U(gen) * (upper - 0.01);
        x = r2(x);
        if (x > remain) x = r2(remain);
        a[i] = x;
        remain = r2(remain - x);
    }
    a.back() = r2(remain); // last takes the remaining amount
    return a;
}

// 1) test for 5 and 10 people (total = 50.00)
void test_send() {
    mt19937 gen(random_device{}());
    cout.setf(ios::fixed); cout << setprecision(2);

    for (size_t n : {5u, 10u}) {
        auto v = send_once(n, 50.0, gen);
        cout << n << ": ";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i) cout << ", ";
            cout << v[i];
        }
        cout << "\n";
    }
}

// 2) P(first > last) over 1e5 runs
void calc_first_vs_last(size_t n) {
    const int T = 100000;
    mt19937 gen(random_device{}());
    int cnt = 0;
    for (int t = 0; t < T; ++t) {
        auto v = send_once(n, 50.0, gen);
        if (v.front() > v.back()) ++cnt;
    }
    cout.setf(ios::fixed); cout << setprecision(3);
    cout << n << ": " << (double)cnt / T << "\n";
}

// 3) Probability each index is the unique largest (1e5 runs)
void calc_probs(size_t n) {
    const int T = 100000;
    mt19937 gen(random_device{}());
    vector<int> win(n, 0);

    for (int t = 0; t < T; ++t) {
        auto v = send_once(n, 50.0, gen);
        double mx = *max_element(v.begin(), v.end());
        int cntmx = 0, idx = -1;
        for (size_t i = 0; i < n; ++i) {
            if (v[i] == mx) { ++cntmx; idx = (int)i; }
        }
        if (cntmx == 1) ++win[idx]; // count only unique maximum
    }

    cout.setf(ios::fixed); cout << setprecision(3);
    cout << n << ": ";
    for (size_t i = 0; i < n; ++i) {
        if (i) cout << ", ";
        cout << (double)win[i] / T;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    test_send();                 // part 1
    calc_first_vs_last(5);       // part 2 (n=5)
    calc_first_vs_last(10);      // part 2 (n=10)
    calc_probs(5);               // part 3 (n=5)
    calc_probs(10);              // part 3 (n=10)
    system("pause");
    return 0;
}
