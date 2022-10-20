// Exercise 14.44:
/*
 Write your own version of a simple desk calculator that can handle binary operations.
*/

#include <functional>
#include <iostream>
#include <map>
#include <string>

int add(int x, int y) { return x + y; }

class Divide {
public:
    double operator() (double x, double y) { return x / y; }
};

auto mod = [] (int x, int y) { return x % y; };

int main()
{
    std::map<std::string, std::function<double(int, int)>> binops = {
        {"+", add},
        {"-", std::minus<int>()},
        {"*", [] (int x, int y) { return x * y; } },
        {"/", Divide()},
        {"%", mod},
    };
    
    int x, y;
    std::string op;
    
    // programme will escape if x or y aren't ints, but returns 0, so not ideal
    // "op" however must be a valid, and key will not be added to map (or called) if it can't be found
    std::cout << "Please enter some basic sums...\n";
    while (std::cin >> x >> op >> y) {
        if (binops.find(op) == binops.end()) { std::cout << "Invalid operator - nice try.\n"; return -1; }
        std::cout << binops[op](x, y) << std::endl;
    }
    
    return 0;
}
