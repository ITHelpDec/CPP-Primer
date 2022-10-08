// Exercise 13.41:
/*
 Why did we use postfix increment in the call to construct inside push_back?
 What would happen if it used the prefix increment?
*/

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

// We used the postfix increment to populate the first_free element with "s"
// If we were to use the prefix increment, we would skip first_free element before trying to populate potentially unallocated memory
