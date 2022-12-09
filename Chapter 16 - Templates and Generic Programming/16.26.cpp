// Exercise 16.26:
/*
 Assuming NoDefault is a class that does not have a default constructor...,
 ...can we explicitly instantiate vector<NoDefault>?
 If not, why not?
 
 >> My initial answer would have been "no", but the following code compiles.
 >> Whilst we have not declared a default constructor, I imagine the compiler has synthesised these for us, thus allowing the following code to run.
*/

#include <vector>
#include <iostream>

class NoDefault {
public:
    void test() { std::cout << "x = " << x << std::endl; }
private:
    int x = 42;
};

int main()
{
    std::vector<NoDefault> ndvec(1);
    ndvec.front().test();
    
    return 0;
}
