// Exercise 9.12:
/*
 Explain the differences between the constructor that takes a container to copy and the constructor that takes two iterators.
 
 (1) A constructor that takes a container to copy must have elements and a container that match
 e.g.
 list<string> authors = {"Milton", "Shakespeare", "Austen"};
 list<string> list2(authors); // ok: types match
 
 (2) For a constructor that takes two iterators, the element type of the container being copied must be compatible with the element type of the new container
 e.g.
 list<string> authors = {"Milton", "Shakespeare", "Austen"};
 deque<string> authList(authors.begin(), it);
*/
