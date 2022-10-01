// Exercise 12.01:
/*
 How many elements do b1 and b2 have at the end of this code?
*/

StrBlob b1;
{
    StrBlob b2 = { "a", "an", "the" };
    b1 = b2;
    b2.push_back("about");
}

// b1 will have have 4 elements at the end of this programme
// { "a", "an", "the", "about" }
// b2 will be destroyed when it goes out of scope, therefore 0 elements
