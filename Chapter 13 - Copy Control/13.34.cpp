// Exercise 13.34:
/*
 Write the Message class as described in this section.
*/

#include <string>
#include <set>
#include <iostream>

class Message;

class Folder {
    // constructors
    
public:
    // "f.addMsg(this);" and "f.remMsg(this)" both return type " Message* "
    void addMsg(Message*) {  }
    void remMsg(Message*) {  }
    
private:
    
};

class Message {
    friend class Folder;
    friend void swap(Message&, Message&);
    friend std::ostream &print(std::ostream&, const Message&);
    
public:
    // constructor
    explicit Message(const std::string &str = "") : contents(str) { }
    
    // copy control to manage pointers to this Message
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    
    // add / remove this Message from the specified Folder's set of messages
    void save(Folder&);
    void remove(Folder&);
    
private:
    std::string contents;
    
    // "folders" is implicity initialised to the empty set
    std::set<Folder*> folders;
    
    // utility functions used by copy constructor assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
};

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
    // for each Folder that holds "s"
    for (auto f : m.folders)
        // add a pointer to this Message to that Folder
        f->addMsg(this);
}

// copy constructor
Message::Message(const Message &m)
{
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
}

void Message::remove_from_Folders()
{
    // for each pointer in folders
    for (auto f : folders)
        // remove this message from that folder
        f->remMsg(this);
    // no Folder points to this message
    folders.clear();
}

Message::~Message()
{
    remove_from_Folders();
}
Message& Message::operator=(const Message &rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

void swap (Message &lhs, Message &rhs)
{
    // not strictly needed, but a good habit
    using std::swap;
    
    // remove pointers to each Message from their (original) respective Folders
    // textbook doesn't use &?
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    
    // swap the contents and Folder pointer sets
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    
    // add pointers to each Message to the their (original) respecitive Folders
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

std::ostream &print(std::ostream &os, const Message &m)
{
    os << m.contents << " ";
    for (const auto &e : m.folders) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    return os;
}

int main()
{
    std::cout << "Creating variables...\n";
    Message m1("man");
    Message m2("bear");
    
    std::cout << "m1 contents : "; print(std::cout, m1);
    std::cout << "m2 contents : "; print(std::cout, m2);

    std::cout << "\nSwapping variables...\n";
    swap(m1, m2);
    std::cout << "m1 contents : "; print(std::cout, m1);
    std::cout << "m2 contents : "; print(std::cout, m2);
    
    std::cout << "\nCreating folders and saving items...\n";
    Folder inbox, drafts, deleted_items;
    m1.save(inbox);
    m2.save(drafts); m2.save(deleted_items);
    std::cout << "m1 contents : "; print(std::cout, m1);
    std::cout << "m2 contents : "; print(std::cout, m2);
    
    std::cout << "\nSwapping variables again...\n";
    swap(m1, m2);
    std::cout << "m1 contents : "; print(std::cout, m1);
    std::cout << "m2 contents : "; print(std::cout, m2);
    
    return 0;
}
