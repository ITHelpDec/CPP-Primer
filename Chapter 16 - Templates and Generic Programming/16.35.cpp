// Exercise 16.35:
/*
 Which, if any, of the following calls are errors?
 If the call is legal, what is the type of T?
 If the call is not legal, what is the problem?

*/

template <typename T> T calc(T t, int i) { return t + i; }
template <typename T> T fcn(T t1, T t2) { return t1 + t2; }

int main()
{
    double d = 3.14;
    float f = 6.28;
    char c = 'a';

    // (a) calc(char, int(char))
    // legal – returns \304
    std::cout << calc(c, 'c') << std::endl;

    // (b) calc(double, int(float))
    // legal – returns 9.14
    std::cout << calc(d, f) << std::endl;

    // (c) fcn(char*, char)
    // legal – return \304
    std::cout << fcn(c, 'c') << std::endl;

    // (d) fcn(double, float)
    // illegal – no matching function (double vs float)
    std::cout << fcn(d, f) << std::endl;
    
    return 0;
}
