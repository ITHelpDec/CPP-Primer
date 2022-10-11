// Exercise 13.55:
/*
 Add an rvalue reference version of push_back to your StrBlob.
*/

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <iostream>
#include <fstream>

class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;
    friend std::istream& readStrBlob(std::istream&, StrBlob&);
    
public:
    typedef std::vector<std::string>::size_type size_type;
    
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob (const StrBlob&);
    StrBlob& operator=(const StrBlob&);
    

    ~StrBlob() { }// { std::cout << "~StrBlob(), destroying shared_ptr -> data.use_count() = " << data.use_count() << std::endl; }
    
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    
    // tweaked original push_back to sow print when it is being called
    void push_back(const std::string &t)
    {
        data->push_back(t);
        std::cout << "(called push_back(const std::string&)" << std::endl;
    }
    
    // rvalue reference push_back
    void push_back(std::string &&t)
    {
        data->push_back(std::move(t));
        std::cout << "(called push_back(std::string&&)" << std::endl;
    }
    
    void pop_back();
    
    std::string& front();
    std::string& back();
    
    const std::string& front() const;
    const std::string& back() const;
    
    StrBlobPtr begin();
    StrBlobPtr end();
    
private:
    std::shared_ptr<std::vector<std::string>> data;
    
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob (const StrBlob &o)
{
    // only one variable - "data"
    // data = o.data; (will increase unt_count)
    //
    // other examples online suggested using "make_shared" like below
    data = std::make_shared<std::vector<std::string>>(*o.data);
    //std::cout << "StrBlob() copy -> data.use_count = " << data.use_count() << std::endl;
}

StrBlob& StrBlob::operator=(const StrBlob &rhs)
{
    // in the dynamically allocated pointers we would have done the following
    // auto temp = std::make_shared<std::vector<std::string>>(*rhs.data);
    // delete data;
    //
    // deleting, however, is controlled by the shared_ptr, so no need to worry about calling it explicitly
    
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
    std::cout << "StrBlob() assign -> data.use_count() = " << data.use_count() << std::endl;
    return *this;
}

class StrBlobPtr {
    friend std::ostream& printStrBlobPtr(std::ostream&, StrBlobPtr&);
public:
    StrBlobPtr() : curr(0) { }
    StrBlobPtr(StrBlob &a, std::size_t sz = 0) : wptr(a.data), curr(sz) { }
    
    std::string& deref() const;
    StrBlobPtr incr();
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>())  { } // { std::cout << "StrBlob() -> data.use_count = " << data.use_count() << std::endl; }
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { }
                                                              

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
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
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

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
        for (auto sbp_it = sbp; i != sbp.deref().size(); sbp_it.incr(), ++i)
            std::cout << sbp_it.deref() << " ";
        std::cout << "\"\n" << std::endl;
    } catch (std::out_of_range err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    } catch (std::exception err) {
        std::cerr << "\"\n" << err.what() << std::endl;
    }
}

int main()
{
    std::cout <<"Creating StrBlob and std::string \"s\"...\n";
    StrBlob sb;
    std::string s = "manbearpig";
    
    std::cout << "\n\"sb.push_back(s)\" should use our const & version...\n";
    sb.push_back(s);
    
    std::cout << "\n\"sb.push_back(\"halfmanhalfbearhalfpig\")\" should use our && version...\n";
    sb.push_back("halfmanhalfbearhalfpig");
    
    return 0;
}
