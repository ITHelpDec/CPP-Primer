// Exercise 18.24:
/*
 On page 807 we presented a series of calls made through a Bear pointer that pointed to a Panda object.
 Explain each call assuming we used a ZooAnimal pointer pointing to a Panda object instead.
*/

void bearPanda() {
    // creates new dynamically-allocated Panda of type "Bear"
    Bear *pb = new Panda("ying_yang");
    
    // calls virtual Panda::print() function to print members
    // this call also exists virtually in ZooAnimal::Bear::,...
    // ...which allows to move further donw the chain to ZooAnimal::Bear::Panda.
    pb->print();
    
    // Despite existing in ZooAnimal::Bear::Panda, ...
    // ZooAnimal::Bear:: does not have a cuddle() function,...
    // ...therefore it cannot be derived
    pb->cuddle();
    
    // similar story with highlight()
    // it exists in ::ZooAnimal and ::Endangered, but not ZooAnimal::Bear,
    // ...therefore it cannot be derived
    pb->highlight();
    
    // make sure to delete dynamically-allocated memory from the heap
    delete pb;
}

void zooAnimalPanda() {
    // creates new dynamically-allocated Panda, this time of type "Endangered"
    ZooAnimal *pz = new Panda("ying_yang");
    
    // calls virtual Panda::print() function to print members
    // virtual call travels via ::ZooAnimal::Bear::Panda::print()
    pz->print();
    
    // exists in ::Panda, but no other base class
    // can therefore not be called
    pz->cuddle();
    
    // only exists in ::Endangered and ::Panda, cannot be called
    pz->highlight();
    
    // same again, make sure to delete dynamically-allocated memory from the heap
    delete pz;
}
