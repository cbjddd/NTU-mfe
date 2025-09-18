#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cmath>
using namespace std;

void q1_1() {
  auto number = 1111111111111111111LL; 
  auto msg = string(" is a prime number!"); 
  cout << number << msg << '\n';
  cout << "type of number is: " << typeid(number).name() << '\n';
  auto x1 = 1; // int
  auto x2 = 1u; // unsigned int
  auto x3 = 1LL; // long long
  auto x4 = 'A'; // char
  auto x5 = string("Hello C++"); // std::string
  auto x6 = 3.14f; // float
  auto x7 = 2.718281828; // double
  cout << "int? " << typeid(x1).name() << ", unsigned? " << typeid(x2).name()
       << ", long long? " << typeid(x3).name() << "char?" << typeid(x4).name()
       << ",string?"<< typeid(x5).name()<<",float"<<typeid(x6).name()<<",double?"<<typeid(x7).name()<<"\n\n";
}

void q1_2() {
  auto i2 = 1024 * 1024 * 1024; // int
  cout << "i2 = " << i2 << '\n';
  cout << "i2 * 2 = " << (i2 * 2) << '\n';
  auto d1 = 1024 * 1024 * 1024 * 4; // int (注意：整型表达式结果再转 double)
  cout << "d1 = " << d1 << '\n';
  cout << "d1 * 2 = " << (d1 * 2) << '\n';
  auto u1 = 25u - 50; // unsigned int
  cout << "u1 = " << u1 << "\n\n";
}
/*
i2 * 2 溢出，因为 int 最大值 2,147,483,647，被超过后结果变成负数
d1 在计算时先用 int 运算，结果 4,294,967,296 超过 int 最大值导致溢出，再把错误的 int 转成 double，所以 d1 的值是错误的负数
这里 u1 是 unsigned int 类型，表达式 25u - 50 中，
25u 是无符号数，和 50（有符号 int）计算时会把 50 转成无符号，
导致结果是一个很大的正数，而不是负数。
这是因为无符号整数不能表示负数，溢出后按模 2^n 运算。
*/



enum class VoucherValue { ONE = 1, TWO = 2, FIVE = 5, TEN = 10 };

struct VoucherV3 {
  VoucherValue value;
  bool spent = false;
};

using HouseholdID = long;

struct Household {
  long id;
  string address;
};

struct HouseholdVouchersV2 {
  HouseholdID id;
  vector<VoucherV3> vouchers;
  int balance;
  bool issued;
  int issued_amount;
};

void issue_50(HouseholdVouchersV2 &hv) {
  for (auto i = 0; i < 5; ++i) hv.vouchers.push_back({VoucherValue::TWO, false}); 
  for (auto i = 0; i < 4; ++i) hv.vouchers.push_back({VoucherValue::FIVE, false}); 
  for (auto i = 0; i < 2; ++i) hv.vouchers.push_back({VoucherValue::TEN, false}); 
  hv.issued = true;
  hv.issued_amount = 50;
  hv.balance = 50;
}

int voucher_to_int(const VoucherV3 &v) {
  return static_cast<int>(v.value);
}

void spend_amount(HouseholdVouchersV2 &hv, int amount_to_spend) {
  for (auto &v : hv.vouchers) { 
    if (amount_to_spend <= 0) break;
    if (!v.spent) {
      auto val = voucher_to_int(v); 
      if (val <= amount_to_spend) {
        v.spent = true;
        hv.balance -= val;
        amount_to_spend -= val;
      }
    }
  }

  auto kept = vector<VoucherV3>{}; 
  kept.reserve(hv.vouchers.size());
  for (const auto &v : hv.vouchers) { 
    if (!v.spent) kept.push_back(v);
  }
  hv.vouchers = kept;
}


void print_hv(const Household &h, const HouseholdVouchersV2 &hv) {
  cout << "Household " << h.id << " @ " << h.address
       << " | issued=" << hv.issued
       << " | issued_amount=" << hv.issued_amount
       << " | balance=" << hv.balance
       << " | n_vouchers=" << hv.vouchers.size() << '\n';
}

void q1_3() {
  auto h1 = Household{1001, "Boonlay 662A #07-336"}; 
  auto h2 = Household{1002, "North Hill Gym #02-02"}; 
  auto h3 = Household{1003, "Pioneer #03-03"}; 
  auto hv1 = HouseholdVouchersV2{h1.id, {}, 0, false, 0}; 
  auto hv2 = HouseholdVouchersV2{h2.id, {}, 0, false, 0}; 
  auto hv3 = HouseholdVouchersV2{h3.id, {}, 0, false, 0}; 
  issue_50(hv1);
  issue_50(hv2);
  issue_50(hv3);
  spend_amount(hv1, 20);
  print_hv(h1, hv1);
  print_hv(h2, hv2);
  print_hv(h3, hv3);
  auto used = 0; // int
  for (const auto &v : hv1.vouchers) { // const VoucherV3&
    if (v.spent) used += voucher_to_int(v);
  }
  cout << "h1 spent = " << used << ", remaining balance = " << hv1.balance << "\n\n";
}

struct Loan {
  double principal;
  int years;
  double rate;
  double interest_due = 0;
};

struct Deposit {
  double principal;
  int years;
  double rate;
  double interest_earned = 0;
};

double compound(double P, double r, int t) {
  return P * pow(1.0 + r, static_cast<double>(t));
}

void q1_4() {
  const auto loanP = 300000.0; 
  const auto loanY = 20; 
  const auto loanR = 0.031; 
  const auto depP = 100000.0; 
  const auto depY = 5; 
  const auto depR = 0.025; 
  Loan L_now = Loan{loanP, loanY, loanR, 0.0}; 
  Deposit D_now = Deposit{depP, depY, depR, 0.0}; 
  Loan L_4y = L_now; 
  Deposit D_4y = D_now; 
  auto L_amount_4 = compound(L_4y.principal, L_4y.rate, 4); 
  L_4y.interest_due = L_amount_4 - L_4y.principal;
  auto D_amount_4 = compound(D_4y.principal, D_4y.rate, 4); 
  D_4y.interest_earned = D_amount_4 - D_4y.principal;
  cout << "Loan(now): P=" << L_now.principal << ", years=" << L_now.years
       << ", r=" << L_now.rate << ", interest_due=" << L_now.interest_due << '\n';
  cout << "Loan(+4y): P=" << L_4y.principal << ", years=" << L_4y.years
       << ", r=" << L_4y.rate << ", interest_due(after 4y)=" << L_4y.interest_due << '\n';
  cout << "Deposit(now): P=" << D_now.principal << ", years=" << D_now.years
       << ", r=" << D_now.rate << ", interest_earned=" << D_now.interest_earned << '\n';
  cout << "Deposit(+4y): P=" << D_4y.principal << ", years=" << D_4y.years
       << ", r=" << D_4y.rate << ", interest_earned(after 4y)=" << D_4y.interest_earned << "\n\n";
}

int main() {
  q1_1();
  q1_2();
  q1_3();
  q1_4();
  system("pause");
  return 0;
}
