#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
    const double m = 70.0;        
    const double c = 3e8;         
    const double J_per_beat = 1.0;  
    const double beats_per_sec = 1.0;
    const double E = m * c * c;
    const double power_J_per_s = J_per_beat * beats_per_sec;
    const double seconds_per_year = 365.25 * 24.0 * 3600.0;
    const double years = E / power_J_per_s / seconds_per_year;
    cout.setf(ios::scientific);
    cout << setprecision(6);

    cout << "Energy contained in 70 kg (J): " << E << endl;
    cout << "Years of heartbeat at 1 J/beat and 1 beat/s: " << years << endl;

    cout.unsetf(ios::scientific);
    cout << fixed << setprecision(2);
    cout << "(~= " << years / 1e9 << " billion years)" << endl;

    system("pause");
    return 0;

}