// Exercise 13.04:
/*
 Assuming Point is a class type with a public copy constructor, identify each use of the copy constructor in this program fragment:
*/

Point global;

Point foo_bar(Point arg) /*...direct...*/
// copy would be Point foo_bar(const Point &arg)
{
    // Point local = arg; "=" – copy
    // Point *heap = new Point (global); "=" – copy
    Point local = arg, *heap = new Point(global);
    
    // "=" – copy
    *heap = local;
    
    // "=" – copy
    Point pa[ 4 ] = { local, *heap };
    
    // nonreference return – copy
    return *heap;
}
