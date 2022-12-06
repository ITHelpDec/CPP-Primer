// Exercise 16.14:
/*
 Write a Screen class template that uses nontype parameters to define the height and width of the Screen.
*/

#include <iostream>

template <typename T> class Screen {
public:
    Screen() { }
    Screen(T height, T width) : height_(height), width_(width) { }
    
    void setResolution(T, T);
    void getResolution();
    
private:
    T height_, width_;
};

template <typename T> inline void Screen<T>::setResolution(T height, T width)
{
    height_ = height;
    width_ = width;
}

template <typename T> inline void Screen<T>::getResolution()
{
    std::cout << "resolution: " << height_ << " x " << width_ << std::endl;
}

int main()
{
    Screen<int> monitor(800, 600);
    monitor.getResolution();
    
    monitor.setResolution(1080, 720);
    monitor.getResolution();
    
    return 0;
}
