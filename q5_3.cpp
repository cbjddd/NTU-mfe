#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "zero_rate_curve.h"   // 提供 RateCurve 与样例曲线 IC

using namespace std;

static RateCurve sort_curve(const RateCurve& src) {
    RateCurve c = src;
    stable_sort(c.begin(), c.end(),[](const auto& a, const auto& b){ return get<0>(a) < get<0>(b); });
    return c;
}

double trans_into_year(int date, int today){
    int days = date - today;
    if(days<0){days=0;}
    return static_cast<double>(days/365);
}

RateCurve parallael_shock(double delta, int today, const RateCurve& rc){
    const double fixed_shock = delta*100;
    RateCurve outcome(rc.size());
    RateCurve sorted_rc=sort_curve(rc);

    transform(sorted_rc.begin(), sorted_rc.end(), outcome.begin(),
              [fixed_shock](const tuple<int,double>& p){
                  auto [d, r] = p;
                  return tuple<int,double>{d, r + fixed_shock};
              });

    return outcome;
}

RateCurve short_risk_shock(double delta, int today, const RateCurve& rc){
    const double shock = delta*100;
    RateCurve outcome(rc.size());
    RateCurve sorted_rc=sort_curve(rc);

    transform(sorted_rc.begin(), sorted_rc.end(), outcome.begin(),
            [shock,today](const tuple<int,double>& p){
                auto [d, r] = p;
                double t = trans_into_year(d, today);
                double slope=exp (-t/4.0);
                double real_shock=slope*shock;
                return tuple<int,double>{d, r + real_shock};
            });

    return outcome;
}

RateCurve rotational_shock(double delta, int today, const RateCurve& rc){
    double positive_or_negative;
    if(delta>0){positive_or_negative=1.0;}
    if(delta<0){positive_or_negative=-1.0;}
    double scale=abs(delta);
    double short_shock=scale*0.03*100.0;
    double long_shock=scale*0.015*100.0;


    RateCurve outcome(rc.size());
    RateCurve sorted_rc=sort_curve(rc);

    transform(sorted_rc.begin(),sorted_rc.end(),outcome.begin(),[today,short_shock,long_shock,positive_or_negative](const tuple<int,double>& p){
        auto [d,r]=p;
        double t=trans_into_year(d,today);
        double w=exp(-t/4.0);
        double real_shock=positive_or_negative*(short_shock*w+long_shock*(1.0-w));
        return tuple<int,double>{d, r + real_shock};
    });

    return outcome;
}

int main(){
    const int today = 41082; 

    cout.setf(ios::fixed); cout << setprecision(6);

    
    auto base = sort_curve(IC);
    auto psh  = parallael_shock(0.02,  today, IC);   
    auto ssh  = short_risk_shock(0.03, today, IC); 
    auto rsh  = rotational_shock(+1.0, today, IC); 

    
    cout << "date       base(%)   parallel(%)  short(%)    rotational(%)"<<endl;
    for (size_t i = 0; i < min<size_t>(5, base.size()); ++i) {
        auto [d0, r0] = base[i];
        auto [d1, r1] = psh[i];
        auto [d2, r2] = ssh[i];
        auto [d3, r3] = rsh[i];
        cout << setw(6) << d0 << "   "
             << setw(8) << r0 << "   "
             << setw(11) << r1 << "   "
             << setw(8) << r2 << "   "
             << setw(12) << r3 << endl;
    }
    system("pause");
    return 0;
}
