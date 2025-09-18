#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;

using RateCurve = vector<tuple<int, double>>;

tuple<vector<int>, vector<double>> split_curve(const RateCurve& rc){
    vector<int> dates(rc.size(),0);
    vector<double> rates(rc.size(),0.0);
    for (size_t i=0;i<rc.size();++i){
        auto [d,r]=rc[i];
        dates[i]=d; rates[i]=r;         
    }
    return {move(dates),move(rates)};
}

void spilt2(const RateCurve& rc,vector<int>& dates,vector<double> &rates){
    dates.resize(rc.size());
    rates.resize(rc.size());
    for(size_t i=0;i<rc.size();++i){
        auto [d,r]=rc[i];
        dates[i]=d; rates[i]=r;
    }
}

double interpolate(const vector<int>& dates,const vector<double>& rates,const int date){
    if (dates.empty() || dates.size() != rates.size())
        throw invalid_argument("dates/rates size mismatch or empty");
    if (date <= dates.front()) return rates.front();
    if (date >= dates.back())  return rates.back();
    vector<int> dates_copy = dates;
    vector<double> rates_copy = rates;
    sort(dates_copy.begin(),dates_copy.end());
    int d1=dates_copy[0];
    int d2=dates_copy[dates.size()-1];
    sort(rates_copy.begin(),rates_copy.end());
    double r1=rates_copy[0];
    double r2=rates_copy[rates.size()-1];
    double current_rate = r1+(r2-r1)*(date-d1)/ (d2 - d1);
    return current_rate;
}

int main() {
    RateCurve IC{
        {41082, 0.0},
        {41083, 0.344720594377147},
        {41085, 0.344720594377147},
        {41092, 0.36836772605730},
        {41116, 0.525507772180778},
        {41146, 0.589858326742378}
    };

    auto [dates, rates] = split_curve(IC);

    cout << fixed << setprecision(12);

    cout << "interp(41080) = " << interpolate(dates, rates, 41080) << endl;
    cout << "interp(41085) = " << interpolate(dates, rates, 41085) << endl;
    cout << "interp(41090) = " << interpolate(dates, rates, 41090) << endl;

    system("pause");
    return 0;
}