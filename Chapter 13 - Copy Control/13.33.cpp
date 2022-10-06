// Exercise 13.33:
/*
 Why is the parameter to the save and remove members of Message a Folder&?
 Why didn’t we define that parameter as Folder?
 Or const Folder&?
 
 >> The parameter to save and remove members of Message is a Folder& because we want to reference and modify the original object.
 >> If we define the parameter without the reference operator (&) then we will be modifying a local copy that will be destroyed out of scope.
 >> If we define it as a const Folder&, then we will be referencing the original object, but will not be able to modify it because it is a "const"
*/
