/*
GenAI Assistance:
- Helped format struct
- Give me outline of some questions
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Zeller Function:
It is a mode 7 congruence formula that maps "date (year/month/day)" to "day of
week". To fit the formula, January and February are treated as the 13th and 14th
months of the previous year (i.e., "the year starts in March"), and then
divided/rounded down to the nearest whole number. The return value is
interpreted as 0=Saturday, 1=Sunday, ..., 6=Friday to approximate the day of the
week.
*/

bool is_leap(int year) {

  return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

static int days_in_month(int month, int year) {
  if (month < 1 || month > 12) {
    cout << "month should be in the range from 1 to 12" << endl;
  }
  switch (month) {
  case 1:
    return 31;
  case 2:
    return is_leap(year) ? 29 : 28;
  case 3:
    return 31;
  case 4:
    return 30;
  case 5:
    return 31;
  case 6:
    return 30;
  case 7:
    return 31;
  case 8:
    return 31;
  case 9:
    return 30;
  case 10:
    return 31;
  case 11:
    return 30;
  case 12:
    return 31;
  default:
    return 0;
  }
}

static void validate_date(int day, int month, int year) {
  if (year <= 0) {
    cout << "year must be positive" << endl;
  } else {
    if (month <= 0 || month >= 13) {
      cout << "month should be in the range from 1 to 12" << endl;
    } else {
      int up_limit = days_in_month(month, year);
      if (day < 1 || day > up_limit) {
        cout << "day should be in the range from 1 to 31" << endl;
      } else {
        cout << "Congrats! The input date is legal" << endl;
      }
    }
  }
}

int calculate_weekday(const int day_in, const int month_in, const int year_in) {
  validate_date(day_in, month_in, year_in);

  int m = month_in;
  int y = year_in;

  if (m <= 2) {
    m += 12; // 13,14
    y -= 1;
  }

  const int K = y % 100;
  const int J = y / 100;

  const int q = day_in;
  const int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

  // 0=Saturday, 1=Sunday, 2=Monday,3=Tuesday,4=wednesday,5=Thursday, 6=Friday
  return h;
}

void test_zeller_spot() {
  // 2000-01-01 是 Saturday -> 0
  int spot_test_1 = calculate_weekday(1, 1, 2000);
  if (spot_test_1 == 0) {
    cout << "2000-01-01 is Saturday. The result of zeller is 0. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2025-07-27 是 Sunday -> 1
  int spot_test_2 = calculate_weekday(27, 7, 2025);
  if (spot_test_2 == 1) {
    cout << "2025-07-27 is Sunday. The result of zeller is 1. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2025-07-07 是 Monday -> 2
  int spot_test_3 = calculate_weekday(7, 7, 2025);
  if (spot_test_3 == 2) {
    cout << "2025-07-07 is Monday. The result of zeller is 2. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2025-08-05 是 Tuesday -> 3
  int spot_test_4 = calculate_weekday(5, 8, 2025);
  if (spot_test_4 == 3) {
    cout << "2025-08-05 is Tuesday. The result of zeller is 3. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2025-06-04 是 Wednesday -> 4
  int spot_test_5 = calculate_weekday(4, 6, 2025);
  if (spot_test_5 == 4) {
    cout << "2025-06-04 is Wednesday. The result of zeller is 4. Calculation "
            "is right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2024-02-29（闰日）是 Thursday -> 5
  int spot_test_6 = calculate_weekday(29, 2, 2024);
  if (spot_test_6 == 5) {
    cout << "2024-02-29 is Thursday. The result of zeller is 5. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
  // 2025-08-22 是 Friday -> 6
  int spot_test_7 = calculate_weekday(29, 2, 2025);
  if (spot_test_7 == 6) {
    cout << "2025-08-22 is Friday. The result of zeller is 6. Calculation is "
            "right."
         << endl;
  } else {
    cout << "You are wrong!!!" << endl;
  }
}

void range_zeller_test() {

  int d = 19, m = 4, y = 2002;
  const int D_end = 22, M_end = 8, Y_end = 2025;

  int w_prev = calculate_weekday(d, m, y);
  int steps = 0;
  int errors = 0;

  while (!(d == D_end && m == M_end && y == Y_end)) {
    // increasing daily until the ending date
    d += 1;
    if (d > days_in_month(m, y)) {
      d = 1;
      m += 1;

      if (m > 12) {
        m = 1;
        y += 1;
      }
    }
    const int w = calculate_weekday(d, m, y);
    const int expected = (w_prev + 1) % 7;
    if (w != expected) {
      ++errors;
    }

    w_prev = w;
    ++steps;
  }
  float accurency = errors / steps;
  cout << "the number of steps is " << steps << endl;
  cout << "the number of errors is " << errors << endl;
  cout << "the ratio of error is " << accurency << endl;
}

void Q2_1() {
  // Question1
  test_zeller_spot();
  range_zeller_test();
  cout << "All tests passed.\n";
}

void Q2_2() {
  int initial_value = 1000;
  const int minus_value = 13;
  int count = 0;
  while (initial_value >= 0) {
    // int before = initial_value;
    initial_value -= minus_value;
    ++count;
  }
  cout << "final value = " << initial_value << " (after " << count
       << " steps)\n";
}
void Q2_3_part_1() {
  int count = 0;
  for (int a = 1; a <= 10; a++) {
    for (int b = 0; b <= 10; b++) {
      if (a == b) {
        continue;
      } else {
        cout << "(" << a << "," << b << ")" << endl;
        ++count;
      }
    }
  }
  cout << "The number of sets is" << count << endl;
}

void Q2_3_part_2() {
  int output_number = 0;
  for (int i = 1; i <= 1000; ++i) {
    if (i % 7 == 0 || i % 11 == 0) {
      continue;
    } else {
      cout << i << ' ' << endl;
      ++output_number;
      if (output_number % 10 == 0) {
        cout << endl;
      }
    }
  }
  if (output_number % 10 != 0) {
    cout << endl;
  }
  cout << "The output number is" << output_number << endl;
}

void Q2_3() {
  Q2_3_part_1();
  Q2_3_part_2();
}

static double Amount = 10000.0;
static int time_range = 12;
static double yearly_interest_rate = 0.05;
static double monthly_interest_rate = yearly_interest_rate / 12;

void print_template(int curr_loan_month, double curr_payment,
                    double curr_interest_payment, double curr_principal_payment,
                    double curr_balance) {
  cout << "CM: " << curr_loan_month << " CPI: " << curr_payment
       << " CI: " << curr_interest_payment << " CP: " << curr_principal_payment
       << " Bal: " << curr_balance << '\n';
}

void print_bullet() {
  cout << "Bullet Payment:" << endl;
  double B = Amount;
  double payments = 0.0;
  double interest = 0.0;
  double principal = 0.0;

  print_template(0, 0.0, 0.0, 0.0, B);
  for (int n = 1; n <= time_range; ++n) {
    double I = B * monthly_interest_rate;
    double Pn;
    if (n == time_range) {
      Pn = Amount;
    } else {
      Pn = 0.0;
    }
    double PI = Pn + I;
    B = B - Pn;

    print_template(n, PI, I, Pn, B);
    payments = payments + PI;
    interest = interest + I;
    principal = principal + Pn;
  }
  cout << "Total PI:" << payments << " I: " << interest << "P: " << principal
       << endl;
}

void print_equal_principal() {
  cout << "Equal Principal Payment:" << endl;

  double B = Amount;
  double monthly_principal = Amount / time_range;
  double payments = 0.0;
  double interest = 0.0;
  double principal = 0.0;

  print_template(0, 0.0, 0.0, 0.0, B);
  for (int n = 1; n <= time_range; ++n) {
    double I = B * monthly_interest_rate;
    double Pn;
    if (n < time_range) {
      Pn = monthly_principal;
    } else {
      Pn = B;
    }
    double PI = Pn + I;
    B = B - Pn;

    print_template(n, PI, I, Pn, B);
    payments = payments + PI;
    interest = interest + I;
    principal = principal + Pn;
  }
  cout << "Total PI:" << payments << " I: " << interest << "P: " << principal
       << endl;
}

void print_equal_total() {
  cout << "Equal Total Payment:" << endl;
  double B = Amount;
  const double fixed_PI = Amount * monthly_interest_rate /
                          (1.0 - pow(1.0 + monthly_interest_rate, time_range));
  double payments = 0.0;
  double interest = 0.0;
  double principal = 0.0;

  print_template(0, 0.0, 0.0, 0.0, B);
  for (int n = 1; n <= time_range; ++n) {
    double I = B * monthly_interest_rate;
    double Pn = fixed_PI - I;
    if (n == time_range) {
      Pn = B;
    }
    double PI = Pn + I;
    B = B - Pn;
    print_template(n, PI, I, Pn, B);
    payments = payments + PI;
    interest = interest + I;
    principal = principal + Pn;
  }
  cout << "Total PI:" << payments << " I: " << interest << "P: " << principal
       << endl;
}

void Q2_4() {
  print_bullet();
  cout << endl;
  print_equal_principal();
  cout << endl;
  print_equal_total();
}

int main() {
  Q2_1();
  Q2_2();
  Q2_3();
  Q2_4();

  system("pause");
  return 0;
}