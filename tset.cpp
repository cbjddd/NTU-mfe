#include <array>
#include <random>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>

using namespace std;

seed_seq seed2{20250916}; 
mt19937 gen_det(seed2); 

array<int, 100> permutation() {
  array<int, 100> perm{};
  for (int i = 0; i < 100; ++i) perm[i] = i;

  for (int i = 99; i >= 1; --i) {
      uniform_int_distribution<int> dist(0, i);
      int j = dist(gen_det);
      swap(perm[i], perm[j]);
  }
  return perm;
}


void test_permutation() {
  const int trials = 1000;
  array<array<unsigned char, 100>, 100> seen{}; 

  for (int t = 0; t < trials; ++t) {
      auto p = permutation();
      for (int i = 0; i < 100; ++i) seen[i][p[i]] = 1;
  }

  for (int i = 0; i < 100; ++i) {
      int distinct = 0;
      for (int v = 0; v < 100; ++v) if (seen[i][v]) ++distinct;
      if (i) cout << ", ";
      cout << distinct;           
  }
  cout <<endl;
}

int main() {
    // 1) 打印一次随机排列，逗号分隔
    auto p = permutation();
    for (int i = 0; i < 100; ++i) {
        if (i) cout << ", ";
        cout << p[i];
    }
    cout << '\n';

    // 2) 进行 1000 次试验并打印统计结果
    test_permutation();
    system("pause");
    return 0;
}