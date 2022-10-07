// Exercise 13.38:
/*
 We did not use copy and swap to define the Message assignment operator.
 Why do you suppose this is so?
*/

// If we were to expand our copy-assignment operator vs the swap function alone, we will see the following:

Message& Message::operator=(const Message &rhs)
{
    // remove_from_Folders();
    for (auto f : folders)
        f->remMsg(this);
    folders.clear();
    
    contents = rhs.contents;
    folders = rhs.folders;
    
    // add_to_Folders(rhs);
    for (auto f : m.folders)
        f->addMsg(this);
    
    return *this;
}

void swap (Message &lhs, Message &rhs)
{
    using std::swap;
    
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

// Hopefully, you will notice that our copy-assignment operator is primarily focussed on changing the lhs (this) of hte equation, as opposed to swap's aim of changing both the left- AND right-hand side of the equation

// I'm sure we could use both copy and swap in some shape or form to make it work, but "swap" in and of itself is already more lines of code than it needs to be, and would require yet more work on top to fix the things we didn't need to change

// our copy-assginment function is less expensive and fit for purpose
