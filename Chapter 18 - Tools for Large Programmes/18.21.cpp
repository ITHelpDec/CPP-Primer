// Exercise 18.21:
/*
 Explain the following declarations. Identify any that are in error and explain why they are incorrect:
 
 (a) class CADVehicle : public CAD, Vehicle { ... };
 (b) class DblList: public List, public List { ... };
 (c) class iostream: public istream, public ostream { ... };
 
*/

// (a) – missing "public" before "Vehicle" class
// class CADVehicle : public CAD, Vehicle { ... };
class Vehicle { };
class CAD { };
class CADVehicle : public CAD, public Vehicle { };

// (b) – "A base class may appear only once in a given derivation list." – pg. 803
// class List { };
// class DblList: public List, public List { ... };

// (c) – risky...these names exist in the standard library...potential namespace pollution
class istream { };
class ostream { };
class iostream: public istream, public ostream { };

