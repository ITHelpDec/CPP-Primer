// Exercise 15.22:
/*
 For the class you chose in the previous exercise, identify some of the likely virtual functions as well as public and protected members.
*/

#include <iostream>
#include <string>

class GFX {
public:
    GFX() = default;
    // ...
    
    // could have a virtual function for applying compression ratio in each file
    // could create an abstract base class to handle compression ratios
    void compress() const;

protected:
    std::size_t width;
    std::size_t height;
private:
    std::string filename;
};

class Compression : public GFX {
public:
    // pure virtual to create abstract base class
    virtual void compress() const = 0;
protected:
    double compression_raio;
};

class gif : public Compression {        // 4:1 - 10:1 compression ratio
    void compress() const override { return width * height * compression_raio; }
};

class tiff : public Compression { };    // 1.4:1 compression ratio
class jpeg : public Compression { };    // 10:1 compression ratio
class bmp : public Compression { };     // uncompressed and loss less
