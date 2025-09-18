/*
Gen AI: Help me sort the outline.
*/
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <cstdint>   // uint64_t

using namespace std;

// ---------- 基础：写/读 POD 类型 ----------
template <class T>
inline void write_pod(ofstream& out, const T& x) {
    out.write(reinterpret_cast<const char*>(&x), sizeof(T));
}
template <class T>
inline void read_pod(ifstream& in, T& x) {
    in.read(reinterpret_cast<char*>(&x), sizeof(T));
}

// ---------- string ----------
void write_string(ofstream& out, const string& str) {
    uint64_t n = static_cast<uint64_t>(str.size());
    write_pod(out, n);
    if (n) out.write(str.data(), static_cast<streamsize>(n));
}

void read_string(ifstream& in, string& str) {
    uint64_t n = 0;
    read_pod(in, n);
    str.resize(static_cast<size_t>(n));
    if (n) in.read(&str[0], static_cast<streamsize>(n)); // C++17: data() 可写
}

// ---------- vector<double> ----------
void write_vector(ofstream& out, const vector<double>& vec) {
    uint64_t n = static_cast<uint64_t>(vec.size());
    write_pod(out, n);
    if (n) out.write(reinterpret_cast<const char*>(vec.data()),
                     static_cast<streamsize>(n * sizeof(double)));
}

void read_vector(ifstream& in, vector<double>& vec) {
    uint64_t n = 0;
    read_pod(in, n);
    vec.resize(static_cast<size_t>(n));
    if (n) in.read(reinterpret_cast<char*>(vec.data()),
                   static_cast<streamsize>(n * sizeof(double)));
}

// ---------- list<int> ----------
void write_list(ofstream& out, const list<int>& lst) {
    uint64_t n = static_cast<uint64_t>(lst.size());
    write_pod(out, n);
    for (int x : lst) write_pod(out, x);
}

void read_list(ifstream& in, list<int>& lst) {
    uint64_t n = 0;
    read_pod(in, n);
    lst.clear();
    for (uint64_t i = 0; i < n; ++i) {
        int x; read_pod(in, x);
        lst.push_back(x);
    }
}

// ---------- 测试结构 ----------
struct Bond {
    string name = "US 10Y Bond";
    list<int> schedule;     // 2021..2030（10 个）
    double price = 100.0;
    vector<double> cashflow; // 9 个 3.0 + 最后 103.0
};

// 打印（验证用）
static void print_bond(const Bond& b) {
    cout << "name      : " << b.name << '\n';
    cout << "schedule  : ";
    for (int y : b.schedule) cout << y << ' ';
    cout << "\nprice     : " << b.price << '\n';
    cout << "cashflow  : ";
    for (double c : b.cashflow) cout << c << ' ';
    cout << "\n";
}

int main() {
    // 1) 构造一个样例 Bond
    Bond a;
    for (int y = 2021; y <= 2030; ++y) a.schedule.push_back(y);
    a.cashflow.assign(10, 3.0);
    a.cashflow.back() = 103.0;

    // 2) 写入二进制文件
    {
        ofstream out("bond.bin", ios::binary);
        if (!out) { cerr << "open bond.bin for write failed\n"; return 1; }
        write_string(out, a.name);
        write_list(out,   a.schedule);
        write_pod(out,    a.price);     // 标量直接写
        write_vector(out, a.cashflow);
    }

    // 3) 读取回到另一个对象
    Bond b;
    {
        ifstream in("bond.bin", ios::binary);
        if (!in) { cerr << "open bond.bin for read failed\n"; return 1; }
        read_string(in, b.name);
        read_list(in,   b.schedule);
        read_pod(in,    b.price);
        read_vector(in, b.cashflow);
    }

    // 4) 打印核对
    cout << "=== original ===\n";  print_bond(a);
    cout << "=== read back ===\n"; print_bond(b);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
