#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
using namespace std;

constexpr int TARGET = 255;

void print_subset(const vector<int>& subset) {
    for (auto x : subset) { cout << x << ", "; }
}

void find_subsets(const vector<int>& S, vector<int>& subset, int index,
                  int sum, int& count, bool debug) {
    if (sum == TARGET) {
        if (debug) print_subset(subset);
        count++;
        return;
    }
    if (index == (int)S.size() || sum > TARGET) return;

    subset.push_back(S[index]);
    find_subsets(S, subset, index + 1, sum + S[index], count, debug);
    subset.pop_back();
    find_subsets(S, subset, index + 1, sum, count, debug);
}

// 要求 2：用 lambda 重写（逻辑保持一致）
int find_subsets_lambda(const vector<int>& S, bool debug) {
    vector<int> subset;
    int count = 0;

    function<void(int,int)> dfs = [&](int idx, int sum) {
        if (sum == TARGET) {
            if (debug) print_subset(subset);
            ++count;
            return;
        }
        if (idx == (int)S.size() || sum > TARGET) return;

        subset.push_back(S[idx]);
        dfs(idx + 1, sum + S[idx]);
        subset.pop_back();
        dfs(idx + 1, sum);
    };

    dfs(0, 0);
    return count;
}

// 要求 3：基础优化版（记忆化）：缓存(index,sum)状态的计数，避免重复计算
int find_subsets_opt(const vector<int>& S) {
    int n = (int)S.size();
    // dp[idx][sum] = 从 idx 开始、当前和为 sum 时的解的个数（-1 表示未计算）
    vector<vector<int>> dp(n + 1, vector<int>(TARGET + 1, -1));

    function<int(int,int)> solve = [&](int idx, int sum) -> int {
        if (sum == TARGET) return 1;
        if (idx == n || sum > TARGET) return 0;
        int& memo = dp[idx][sum];
        if (memo != -1) return memo;
        // 选或不选当前元素
        int take = solve(idx + 1, sum + S[idx]);
        int skip = solve(idx + 1, sum);
        return memo = (take + skip);
    };

    return solve(0, 0);
}

void q3_test() {
    const vector<vector<int>> Ss{
        {1, 3, 5, 11, 13, 21, 31, 33, 35, 37, 41, 43, 51, 53, 55},      // 167
        {255, 1, 3, 5, 11, 13, 21, 31, 33, 35, 37, 41, 43, 51, 53, 55}   // 168
    };

    for (const auto& S : Ss) {
        vector<int> subset;
        int count = 0;
        find_subsets(S, subset, 0, 0, count, false);
        cout << "Total number of subsets with sum 255: " << count << "\n\n";
    }

    // 要求 1：测量原函数运行时间（debug=false，迭代 1e5 次）
    const int iterations = 100000;

    {
        const auto& S = Ss[0];
        vector<int> subset;
        int sink = 0; // 防止过度优化
        auto t0 = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            int count = 0;
            subset.clear();
            find_subsets(S, subset, 0, 0, count, false);
            sink += count;
        }
        auto t1 = chrono::high_resolution_clock::now();
        cout << "find_subsets x " << iterations << " time (ms): "
             << chrono::duration<double, milli>(t1 - t0).count() << "\n";
        (void)sink;
    }

    // lambda 版本计时（同样 1e5 次）
    {
        const auto& S = Ss[0];
        int sink = 0;
        auto t0 = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            sink += find_subsets_lambda(S, false);
        }
        auto t1 = chrono::high_resolution_clock::now();
        cout << "lambda version x " << iterations << " time (ms): "
             << chrono::duration<double, milli>(t1 - t0).count() << "\n";
        (void)sink;
    }

    // 优化版（记忆化）计时（同样 1e5 次）
    {
        const auto& S = Ss[0];
        int sink = 0;
        auto t0 = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            sink += find_subsets_opt(S);
        }
        auto t1 = chrono::high_resolution_clock::now();
        cout << "find_subsets_opt x " << iterations << " time (ms): "
             << chrono::duration<double, milli>(t1 - t0).count() << "\n";
        (void)sink;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    q3_test();
    system("pause");
    return 0;
}
