// Exercise 16.38:
/*
 When we call make_shared (§ 12.1.1, p. 451), we have to provide an explicit template argument.
 Explain why that argument is needed and how it is used.
*/

#include <memory>
#include <string>
#include <vector>

std::shared_ptr<int> p3 = std::make_shared<int>(42);
std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
std::shared_ptr<int> p5 = std::make_shared<int>();

auto p6 = std::make_shared<std::vector<std::string>>();
auto p = std::make_shared<int>(42);


/*
 >> When we call std::make_shared<T>, "we are constructing an object of type T and wrapping it in a std::shared_ptr using args as the parameter list the constructor of T".
 >> https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
*/

template <class T, class... Args> std::shared_ptr<T> make_shared(Args&&... args);

/*
 >> "The storage is typically larger than sizeof(T) in order to use one allocation for both the control block of the shared pointer and the T object. " i.e. we need to know how much space we are allocating
*/

