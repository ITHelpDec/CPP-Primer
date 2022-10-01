// Exercise 12.19:
/*
 Define your own version of StrBlobPtr and update your StrBlob
 class with the appropriate friend declaration and begin and end members.
 
 >> Other examples have used header files, and given the length of the code, this seems like a good idea
 >> I will consider this in future lengthier projects
*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>

class StrBlobPtr;

class StrBlob {
    // NEW
    friend class StrBlobPtr;
    
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
    
    // NEW (x2)
    StrBlobPtr begin();
    StrBlobPtr end();
    
private:
    std::shared_ptr<std::vector<std::string>> data;
    
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// StrBlobPtr throws an exception on attempts to access a non-existent element
class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) { }
    StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    std::string& deref() const;
    StrBlobPtr incr();  // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    // is the vector still around?
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, reurn a shared_ptr to the vector
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];  // (*p) is the vector to which this object points
}

// prefix returns a reference to the incremenetal object
StrBlobPtr StrBlobPtr::incr()
{
    // if curr already points apst the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr; // advance the current state
    return *this;
}

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

// NEW (x2)
// defined within StrBlob class or type StrBlobPtr
StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

// create function to try each StrBlob
void tryStrBlob(StrBlob &sb)
{
    try {
        std::cout << "First element: " << sb.front() << "\nFinal Element: " << sb.back() << std::endl;
    } catch (std::out_of_range err) {
        std::cerr << err.what() << std::endl;
    } catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }
    std::cout << std::endl;
}

void tryStrBlobPter(StrBlobPtr &sbp)
{
    int i = 0;
    try {
        for (auto sbp_it = sbp; i != sbp.deref().size() ; sbp_it.incr(), ++i)
            std::cout << sbp_it.deref() << " ";
        std::cout << std::endl << std::endl;
    } catch (std::out_of_range err) {
        std::cerr << err.what() << std::endl;
    } catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }
}

int main()
{
    // Test all public members of StrBlob
    std::cout << "Test #1:\n";
    StrBlob sb1;
    tryStrBlob(sb1);
    
    std::string s = "manbearpig";
    std::cout << "Test #2 – inserting \"" << s << "\"\n";
    sb1.push_back(s);
    tryStrBlob(sb1);
    
    std::cout << "Test #3 – removing \"" << s << "\"\n";
    sb1.pop_back();
    tryStrBlob(sb1);
    
    std::cout << "Test #4 – is \"" << s << "\" empty?\n";
    std::cout << (sb1.empty() == 1 ? "Yes.\n" : "No.\n") << std::endl;
    
    std::cout << "Test #5:\n";
    std::cout << "sb1 has "<< sb1.size() << (sb1.size() == 1 ? " element.\n" : " elements.\n") << std::endl;
    
    // Test all public members of StrBlobPtr
    std::cout << "Test #6:\n";
    std::cout << "Creating new StrBlobPtr: sbp1" << std::endl;
    StrBlobPtr sbp1;
    std::cout << "sbp1: " << &sbp1 << std::endl << std::endl;
    
    std::cout << "Test #7:\n";
    std::cout << "Creating new StrBlobPtr (sbp2 with the contents os sb2):" << std::endl;
    // create and push_back to sb2
    StrBlob sb2;
    sb2.push_back("man");
    sb2.push_back("bear");
    sb2.push_back("pig");
    // make a StrBlobPtr from StrBlob and itreate through contents
    StrBlobPtr sbp2(sb2);
    tryStrBlobPter(sbp2);
    
    // the above function expands to the following until it reaches and out_of_range error
    //
    // std::cout << sbp2.deref() << " " << sbp2.incr().deref() << " " << sbp2.incr().deref() << std::endl;
    
    return 0;
}
