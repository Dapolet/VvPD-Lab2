#include <iostream>
#include <vector>

int main()
{
    const std::vector<int> values{10, 20, 30, 40, 50};

    for (const auto value : values) {
        std::cout << value << '\n';
    }
    return 0;
}
