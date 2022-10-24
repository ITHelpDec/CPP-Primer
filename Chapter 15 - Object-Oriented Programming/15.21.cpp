// Exercise 15.21:
/*
 Choose one of the following general abstractions containing a family of types (or choose one of your own).
 Organize the types into an inheritance hierarchy:

 (a) Graphical file formats (such as gif, tiff, jpeg, bmp)
 (b) Geometric primitives (such as box, circle, sphere, cone)
 (c) C++ language types (such as class, function, member function)
 
 >> I've chosen (b)
*/

class GFX { };

class animated : public GFX { };
class still : public GFX { };

class gif : public animated { };
class tiff : public still { };
class jpeg : public still { };
class bmp : public still { };
