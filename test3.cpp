    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <functional>
    #include <chrono>

    using namespace std;

    void print_subset(const vector<int>& subset) {
        for (auto x : subset) { cout << x << ", "; }
    }

    void find_subsets(const vector<int>& S, vector<int>& subset, int index,
                    int sum, int& count, bool debug) {
        if (sum == 255) {
            if (debug) print_subset(subset);
            count++;
            return;
        }
        if (index == (int)S.size() || sum > 255) return;

        subset.push_back(S[index]);
        find_subsets(S, subset, index + 1, sum + S[index], count, debug);
        subset.pop_back();
        find_subsets(S, subset, index + 1, sum, count, debug);
    }

    // —— 用 lambda 改写 —— //
    void find_subsets_lambda(const vector<int>& S, vector<int>& subset, int index,
                            int sum, int& count, bool debug) {
        function<void(int,int)> dfs = [&](int i, int cur) {
            if (cur == 255) {
                if (debug) print_subset(subset);
                count++;
                return;
            }
            if (i == (int)S.size() || cur > 255) return;

            subset.push_back(S[i]);
            dfs(i + 1, cur + S[i]);
            subset.pop_back();
            dfs(i + 1, cur);
        };
        dfs(index, sum);
    }

    // —— 优化版：降序排序 + 后缀和上界剪枝 + 包含分支越界检查 —— //
    void find_subsets_opt(const vector<int>& S, vector<int>& subset, int index,
                        int sum, int& count, bool debug) {
        vector<int> A(S.begin(), S.end());
        sort(A.begin(), A.end(), greater<int>());              // 大的数先放，便于早剪枝
        vector<int> suffix(A.size() + 1, 0);                   // suffix[i] = A[i..] 的和
        for (int i = (int)A.size() - 1; i >= 0; --i) suffix[i] = suffix[i + 1] + A[i];

        function<void(int,int)> dfs = [&](int i, int cur) {
            if (cur == 255) {                                  // 命中
                if (debug) print_subset(subset);
                count++;
                return;
            }
            if (i == (int)A.size() || cur > 255) return;       // 越界/超和
            if (cur + suffix[i] < 255) return;                 // 即使全取也不可能达标

            int v = A[i];
            if (cur + v <= 255) {                              // 仅当不会超和才尝试“取”
                subset.push_back(v);
                dfs(i + 1, cur + v);
                subset.pop_back();
            }
            dfs(i + 1, cur);                                   // 不取
        };
        dfs(index, sum);
    }

    void q3_test() {
        const vector<vector<int>> Ss{
            {1, 3, 5, 11, 13, 21, 31, 33, 35, 37, 41, 43, 51, 53, 55}, // 167
            {255, 1, 3, 5, 11, 13, 21, 31, 33, 35, 37, 41, 43, 51, 53, 55}
        };

        for (const auto& S : Ss) {
            vector<int> subset;
            int count = 0;
            find_subsets(S, subset, 0, 0, count, false);
            cout << "Total number of subsets with sum 255: " << count << "\n\n";
        }
    }

    int main() {
        q3_test();

        const vector<int> S = {1, 3, 5, 11, 13, 21, 31, 33, 35, 37, 41, 43, 51, 53, 55};
        const int ITER = 100000;

        // 1) 计时：原版
        {
            auto t0 = chrono::steady_clock::now();
            long long sink = 0;
            for (int it = 0; it < ITER; ++it) {
                vector<int> subset;
                int count = 0;
                find_subsets(S, subset, 0, 0, count, false);
                sink += count;
            }
            auto t1 = chrono::steady_clock::now();
            cout << "find_subsets: "
                << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
                << " ms\n";
            if (sink == -1) cout << "";
        }

        // 2) 计时：lambda 版
        {
            auto t0 = chrono::steady_clock::now();
            long long sink = 0;
            for (int it = 0; it < ITER; ++it) {
                vector<int> subset;
                int count = 0;
                find_subsets_lambda(S, subset, 0, 0, count, false);
                sink += count;
            }
            auto t1 = chrono::steady_clock::now();
            cout << "find_subsets (lambda): "
                << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
                << " ms\n";
            if (sink == -1) cout << "";
        }

        // 3) 计时：优化版
        {
            auto t0 = chrono::steady_clock::now();
            long long sink = 0;
            for (int it = 0; it < ITER; ++it) {
                vector<int> subset;
                int count = 0;
                find_subsets_opt(S, subset, 0, 0, count, false);
                sink += count;
            }
            auto t1 = chrono::steady_clock::now();
            cout << "find_subsets_opt: "
                << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
                << " ms\n";
            if (sink == -1) cout << "";
        }
        system("pause");
        return 0;
    }
