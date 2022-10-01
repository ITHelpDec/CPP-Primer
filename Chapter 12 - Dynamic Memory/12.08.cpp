// Exercise 12.08:
/*
 Explain what if anything is wrong with the following function.
*/

bool b()
{
    int* p = new int;
    // ...
    return p;
}

// the return type is bool instead of int* (this could result in a memory leak)
