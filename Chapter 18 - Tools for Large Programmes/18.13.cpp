// Exercise 18.13:
/*
 When might you use an unnamed namespace?
 
 >> Unnamed namespaces have a finite lifetime – we might want to use one if we have a very specific template specialisation (e.g. std::hash) that we dont want to span across across multiple files.
 
 >> Apparently, encapsulating your code in an unnamed namespace also forces implicit inlining for performance improvements, but there are mixed opinions on this.
 
 >> Please see the following link as an examle running a Mandelbrot benchmark with unnamed namespaces.
 >> https://benchmarksgame-team.pages.debian.net/benchmarksgame/program/mandelbrot-gpp-4.html
 
*/
