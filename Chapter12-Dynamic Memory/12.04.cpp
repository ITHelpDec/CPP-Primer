// Exercise 12.04:
/*
 In our check function we didn’t check whether i was greater than zero.
 Why is it okay to omit that check?
*/

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(&msg);
}


// Because "i" (std::vector<std::string>::size_type) is unsigned, it will always return a positive integer greater than 0, even if "i" is assigned to a negative number.
