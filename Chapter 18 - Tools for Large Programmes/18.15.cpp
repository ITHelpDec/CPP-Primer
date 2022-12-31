// Exercise 18.13:
/*
 Explain the differences between using declarations and directives.
 
 >> "A using declaration introduces only one namespace member at a time. It allows us to be very specific regarding which names are used in our programs."  – pg. 793, e.g.
*/

#include <iostream>
using std::cout;

int main()
{
    cout << "manbearpig" << std::endl;
    // ...instead of...
    // std::cout <<
    
    return 0;
}
/*
 >> They also obey all normal scope rules
*/

/*
 "A using directive...allows us to use the unqualified form of a namespace name. Unlike a using declaration, we retain no control over which names are made visible – they all are." – pg. 793
 
 >> This is convenient, but also dangerous, potentially leading to global namespace problems for programmes that make use of multiple libraries e.g. the common one we all learn...
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "manbearpig" << endl;
    // ...instead of...
    // std::cout << "manbearpig" << std::endl;
    
    return 0;
}

/*
 ...it just feels so wrong...
*/
