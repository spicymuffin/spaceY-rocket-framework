#include <iostream>

int main()
{
    if (__cplusplus == 202101L)
        std::printf("C++23";
    else if (__cplusplus == 202002L)
        std::printf("C++20";
    else if (__cplusplus == 201703L)
        std::printf("C++17";
    else if (__cplusplus == 201402L)
        std::printf("C++14";
    else if (__cplusplus == 201103L)
        std::printf("C++11";
    else if (__cplusplus == 199711L)
        std::printf("C++98";
    else
        std::printf("pre-standard C++." << __cplusplus;
    std::printf("\n";
}