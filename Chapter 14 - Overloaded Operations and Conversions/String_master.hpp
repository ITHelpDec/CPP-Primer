#ifndef String_hpp
#define String_hpp

#include <iostream>
#include <initializer_list>
#include <memory>

class String {
    friend std::ostream &operator<<(std::ostream&, const String&);
    
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    
    friend bool operator<(const String&, const String&);
    friend bool operator>(const String&, const String&);
    friend bool operator<=(const String&, const String&);
    friend bool operator>=(const String&, const String&);
    
public:
    String();
    String(const char*);
    String(std::initializer_list<char>&&);
    
    String(const String&);
    String& operator=(const String&);
    
    String(String&&) noexcept;
    String& operator=(String&&) noexcept;
    
    // destroy
    ~String();
    
    // "[]" operators
    char& operator[](std::size_t&);
    const char& operator[](std::size_t&) const;
    
    void push_back(const char&);
    void pop_back();
    
    bool empty() const;
    std::size_t size() const;
    std::size_t capacity() const;
    
    char *begin() const { return cp; }
    char *end() const { return offtheend; }
    const char *cbegin() const { return begin(); }
    const char *cend() const { return end(); }
    
private:
    static std::allocator<char> alloc;
    
    void free();
    void reallocate(const std::size_t&);
    
    char *cp;
    char *offtheend;
    char *cap;
};

#endif /* String_hpp */
