// Exercise 12.02:
/*
 Write your own version of the StrBlob class including the const versions of front and back.
*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;
    
    // default constructor
    StrBlob();

    StrBlob(std::initializer_list<std::string> il);
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    
    // element access for modification
    std::string& front();
    std::string& back();
    
    // element access for only reading

    const std::string& front() const;
    const std::string& back() const;
    
    // const on the end refers to the trailing "this"
    // read...
    // const std::string& front() const;
    // like
    // const std::string& front(const StrBlob *this);
    // the trailing this cannot be modified in these instances
    
private:
    std::shared_ptr<std::vector<std::string>> data;
    
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};
                                                              
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { }
                                                              

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

const std::string& StrBlob::front() const
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

int main()
{
    // std::vector<std::string> svec;
    std::string s = "Hello";
    
    StrBlob sb1;
    
    std::cout << "sb1 size is: " << sb1.size() << std::endl;
    std::cout << "Is sb1 currently empty? " << (sb1.empty() == 1 ? "Yes." : "No") << std::endl;
    
    std::cout << "Adding \"" << s << "\"" << std::endl;
    sb1.push_back(s);
    
    std::cout << "sb1 size is now: " << sb1.size() << std::endl;
    std::cout << "Is sb1 currently empty? " << (sb1.empty() == 1 ? "Yes." : "No") << std::endl;
    std::cout << "The first element is " << sb1.front() << std::endl;
    std::cout << "The last element is " << sb1.back() << std::endl;
    
    std::cout << "Removing \"" << s << "\"" << std::endl;
    sb1.pop_back();
    
    std::cout << "sb1 size is now: " << sb1.size() << std::endl;
    std::cout << "Is sb1 currently empty? " << (sb1.empty() == 1 ? "Yes." : "No") << std::endl;
    
    std::cout << "Adding 10 elements of \"" << s << "\"" << std::endl;
    for (auto i = 0; i != 10; ++i)
        sb1.push_back(s);
    
    std::cout << "sb1 size is now: " << sb1.size() << std::endl;
    std::cout << "Is sb1 currently empty? " << (sb1.empty() == 1 ? "Yes." : "No") << std::endl;
    
    return 0;
}
