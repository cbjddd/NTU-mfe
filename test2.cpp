#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;

int find_key(const string& s) {
    int freq[26] = {0};
    for (unsigned char c : s) {
        if (c >= 'a' && c <= 'z') freq[c - 'a']++;
    }
    int idx_max = 0;
    for (int i = 1; i < 26; ++i) if (freq[i] > freq[idx_max]) idx_max = i;
    return 4 - idx_max; // 'e' 的索引是 4
}

void encrypt(const string& s, int key) {
    for (unsigned char c : s) {
        if (c >= 'a' && c <= 'z') {
            int x = (c - 'a' + key) % 26;
            if (x < 0) x += 26;
            cout << char('a' + x);
        } else {
            cout << c;
        }
    }
    cout << '\n';
}

int main() {
    auto encrypted_text =
        "wb o gaozz jwzzous bsghzsr oawrgh gdfokzwbu twszrg, hvsfs zwjsr o viapzs tofasf boasr shvob. vwg rowzm fcihwbs fsjczjsr ofcibr hsbrwbu hc vwg qfcdg obr qofwbu tcf vwg obwaozg. sjsfm acfbwbu, vs fcgs sofzm, sousf hc sapfoqs hvs sbsfum ct hvs sofhv. kwhv ibkojsfwbu rsrwqohwcb, vs dzcksr hvs zobr, gcksr hvs gssrg, obr bifhifsr hvsa kwhv hsbrsf qofs. sjsbwbug ksfs gdsbh wb qcbhsbhasbh, og vs kohqvsr hvs gib usbhzm rsgqsbr psvwbr hvs rwghobh vwzzg. vwg zcjs tcf vwg zobr obr whg pcibhwtiz cttsfwbug ybsk bc pcibrg. shvob'g gwadzs zwts slsadzwtwsr hvs sggsbqs ct vofr kcfy, vcds, obr vofacbm kwhv bohifs."s;

    int key = find_key(encrypted_text);
    cout << key << '\n';
    encrypt(encrypted_text, key);
    system("pause");
    return 0;
}

