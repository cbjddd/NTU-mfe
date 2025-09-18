#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h> // 用于解码 typeid().name()

std::string demangle(const char* name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
    std::string result(name);
    if (status == 0 && demangled) {
        result = demangled;
        free(demangled);
    }
    return result;
}

int main() {
    // 用 auto 存储数字
    auto number = 1111111111111111111LL; // 如果不加 LL，可能被推断为 int 或 long long
    std::string message = " is a prime number!";

    std::cout << number << message << std::endl;

    // 查看变量类型
    std::cout << "Type of number: " << demangle(typeid(number).name()) << std::endl;
    std::cout << "Type of message: " << demangle(typeid(message).name()) << std::endl;

    // 多个变量测试类型推断
    auto a = 111;                       // int
    auto b = 1111111111;                // int (32 位)
    auto c = 1111111111111111111;       // long long（64 位）
    auto d = 1111111111111111111LL;     // long long（显式）

    std::cout << "Type of a: " << demangle(typeid(a).name()) << std::endl;
    std::cout << "Type of b: " << demangle(typeid(b).name()) << std::endl;
    std::cout << "Type of c: " << demangle(typeid(c).name()) << std::endl;
    std::cout << "Type of d: " << demangle(typeid(d).name()) << std::endl;
    system("pause");
    return 0;
}
