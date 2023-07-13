#include <iostream>

struct AnyType
{
    template <typename T>
    operator T();
};

template <typename T, typename = void, typename... Ts>
struct CountMember
{
    constexpr static size_t value = sizeof...(Ts) - 1;
};

template <typename T, typename... Ts>
struct CountMember<T, std::void_t<decltype(T{Ts{}...})>, Ts...>
{
    constexpr static size_t value = CountMember<T, void, Ts..., AnyType>::value;
};

int main(int argc, char **argv)
{
    struct Test
    {
        int a;
        int b;
        int c;
        int d;
    };
    std::cout << CountMember<Test>::value << std::endl;
    return 0;
}