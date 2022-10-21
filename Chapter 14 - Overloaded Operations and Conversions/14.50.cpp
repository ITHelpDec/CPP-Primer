// Exercise 14.50:
/*
 Show the possible class-type conversion sequences for the initializations of ex1 and ex2.
 Explain whether the initializations are legal or not.
 */

struct LongDouble {
    LongDouble(double = 0.0);
    operator double();
    operator float();
   };

int main()
{
    LongDouble ldObj;   // fine (double)
    int ex1 = ldObj;    // error (ambiguous)
    float ex2 = ldObj;  // fine (float conversion)
    
    return 0;
}
