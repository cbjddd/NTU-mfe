#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <stdexcept>
#include "zero_rate_curve.h"   

using namespace std;

static double interpolate(const RateCurve& curve, int end_date) {
    if (curve.empty()) throw runtime_error("empty rate curve");

    // 假定 curve 已按日期升序
    if (end_date <= get<0>(curve.front()))
        return get<1>(curve.front());
    if (end_date >= get<0>(curve.back()))
        return get<1>(curve.back());

    for (size_t i = 0; i + 1 < curve.size(); ++i) {
        int d1 = get<0>(curve[i]);
        int d2 = get<0>(curve[i + 1]);
        if (d1 <= end_date && end_date <= d2) {
            double r1 = get<1>(curve[i]);
            double r2 = get<1>(curve[i + 1]);
            if (d2 == d1) return r1; 
            double w = (end_date - d1) * 1.0 / (d2 - d1);
            return r1 + (r2 - r1) * w;
        }
    }
}

double get_df(int end_date, const RateCurve& ic, int today) {
    double r_percent = interpolate(ic, end_date); 
    double days_diff = static_cast<double>(end_date - today);
    double df = exp(-(days_diff / 365.0) * (r_percent / 100.0));
    return df;
}

double bond_price_zero(double face_value, double coupon_rate,
                       double maturity, const string& ps,
                       int today, const RateCurve& ic, double ic_spread  = 0.0) {
    int k = 0;
    if (ps == "A") k = 1;
    else if (ps == "S") k = 2;
    else if (ps == "Q") k = 4;
    else {
        cout<<"Wrong Type!"<<endl;
    }
    const int N = static_cast<int>(round(maturity * k));


    const double coupon_each = face_value * coupon_rate / k;


    double price = 0.0;
    for (int i = 1; i <= N; ++i) {
        int end_date = today + static_cast<int>(round(365.0 * i / k));
        double df = get_df(end_date, ic, today);
        double cf = coupon_each;
        if (i == N) cf += face_value; 
        price += df * cf;
    }
    return price;
}

int main() {
    double v00 = bond_price_zero(100, 0.02, 4, "Q", 41082, IC, 0.0);
    double v01 = bond_price_zero(100, 0.03, 2, "S", 41082, IC, 0.0);
    double v02 = bond_price_zero(100, 0.04, 3, "A", 41082, IC, 0.0);

    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "v00: " << v00 << "  (expected ~100.579)"<<endl;
    cout << "v01: " << v01 << "  (expected ~103.281)"<<endl;
    cout << "v02: " << v02 << "  (expected ~106.992)"<<endl;
    system("pause");
    return 0;
}