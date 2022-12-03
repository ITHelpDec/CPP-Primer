// Example 16.09:
/*
 What happens when a class template is instantiated?
 
 >> "As we've seen many times, when we use a class template, we must supply extra information. We can now see that that extra information is a list of explicit tepmlate arguments that are bound to the templates parameters. The compiler uses these template arguments to instantiate a specific class from the template." – pg. 660
*/

// e.g.

Blob<int>ia;                        // empty Blob<int>
Blob<int> ia2 = { 0, 1, 2, 3, 4};   // Blob<int> with five elements

// ...instantiates...

template <>
class Blob<int> {
public:
    typedef typename std::vector<int>::size_type size_type;
    Blob();
    Blob(std::initializer_list<int> il);
    // ...
    int& operator[](size_type i);
private:
    std::shared_ptr<std::vector<int>> data;
    void check(size_type i, const std::string &msg) const;
};

// ...in place of...

template <typename T>
class Blob {
public:
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(std::initializer_list<int> il);
    // ...
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

/*

 >> "When the compiler instanties a class from our Blob template, it rewrites the Blob template, replacing each instance of the template parameter T by the given template argument, which in this case is int" – pg. 660
 
*/
