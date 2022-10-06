// Exercise 13.35:
/*
 What would happen if Message used the synthesized versions of the copy-control members?
 
 >> If we were to use synthesised versions of the copy-control members, there would be a breakdown in communication between the Messages and the Folders – the Messages would know they've changed locations...
 
 // contents = m.contents;
 // folders = m.folders;
 
 >> ...but the Folders wouldn't, because there is no call to...
 
 // remove_from_Folders();
 // or
 // add_to_Folders();
 
*/
