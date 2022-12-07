// Exercise 16.15:
/*
 Implement input and output operators for your Screen template. Which, if any, friends are necessary in class Screen to make the input and output operators work? Explain why each friend declaration, if any, was needed.
 
 >> Similar to other exercises, ">>" and "<<" operators were declared as friends, such that they have access to our class' private member variables.
 
 >> The forward-declaration techniques from previous examples on other operators were used to allow the code to run.
*/

#include <iostream>

template <typename> class Screen;

template <typename T> std::istream& operator>>(std::istream&, Screen<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, const Screen<T>&);

template <typename T> class Screen {
    friend std::istream& operator>> <T>(std::istream&, Screen<T>&);
    friend std::ostream& operator<< <T>(std::ostream&, const Screen<T>&);
public:
    Screen() { }
    Screen(T height, T width) : height_(height), width_(width) { }
    
    void setResolution(T, T);
    void getResolution();
private:
    T height_ = 0, width_ = 0;
};

template <typename T> inline void Screen<T>::setResolution(T height, T width)
{
    height_ = height;
    width_ = width;
}

template <typename T> inline void Screen<T>::getResolution()
{
    std::cout << "Resolution: " << height_ << " x " << width_ << std::endl;
}

template <typename T> inline std::istream& operator>> (std::istream &is, Screen<T> &monitor)
{
    return (is >> monitor.height_ >> monitor.width_);
}

template <typename T> inline std::ostream& operator<< (std::ostream &os, const Screen<T> &monitor)
{
    return (os << monitor.height_ << " x " << monitor.width_);
}

int main()
{
    Screen<int> monitor;
    
    std::cout << "Current resolution: " << monitor << std::endl;
    
    std::cout << "\nPlease enter a height, followed by a width: ";
    std::cin >> monitor;
    
    std::cout << "\nNew resolution: " << monitor << std::endl;
    
    return 0;
}
