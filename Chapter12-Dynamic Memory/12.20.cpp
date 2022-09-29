// Exercise 12.20:
/*
 Write a program that reads an input file a line at a time into a StrBlob
 and uses a StrBlobPtr to print each element in that StrBlob.
*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>
#include <fstream> // NEW

class StrBlobPtr;

class StrBlob {
    // NEW
    friend class StrBlobPtr;
    friend std::istream& readStrBlob(std::istream&, StrBlob&);
    
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
    friend std::ostream& printStrBlobPtr(std::ostream&, StrBlobPtr&);
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
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

// create function to try each StrBlob
void readStrBlob(std::ifstream &file, StrBlob &sb)
{
    std::string line;
    while (std::getline(file, line))
        sb.push_back(line);
}

void printStrBlobPter(StrBlobPtr &sbp)
{
    int i = 0;
    std::cout << "\" ";
    try {
        //for (auto sbp_it = sbp; i != sbp.deref().size(); sbp_it.incr(), ++i)
        for (auto sbp_it = sbp; i != sbp.deref().size(); sbp_it.incr(), ++i)
            std::cout << sbp_it.deref() << " ";
        std::cout << "\"\n" << std::endl;
    } catch (std::out_of_range err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    } catch (std::exception err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc < 1) {
        std::cerr << "Please supply an input and output file.\n" << std::endl;
        return -1;
    }
    
    if (argc > 2) {
        std::cerr << "Too many arguments supplied.\n" << std::endl;
        return -1;
    }
    
    std::ifstream in(argv[1]);
    
    if (!in.is_open()) {
        std::cerr << "Unable to open file – closing programme." << std::endl;
        return -1;
    }
    std::cout << "File opened successfully – carrying out rest of programme.\n" << std::endl;
    
    // create empty StrBlob
    StrBlob sb;
    // read standard input into sb
    readStrBlob(in, sb);
    
    // close input file
    in.close();
        
    // create StrBlobPtr using contents of sb
    StrBlobPtr sbp(sb);
    // print sbp
    printStrBlobPter(sbp);
    
    return 0;
}
