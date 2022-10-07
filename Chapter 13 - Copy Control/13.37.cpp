// Exercise 13.37:
/*
 Add members to the Message class to insert or remove a given Folder* into folders.
 These members are analogous to Folder’s addMsg and remMsg operations.
 
 >> See lines 62-64
*/

#include <string>
#include <set>
#include <iostream>

class Message;

class Folder {
    friend void swap(Message&, Message&);
    friend class Message;
    friend std::ostream &printFolder(std::ostream&, Folder&);
    
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    
    void save(Message&);
    void remove(Message&);
    
    std::size_t size() { return messages.size(); }
    
private:
    std::set<Message*> messages;
    
    void add_to_Message_locations(const Folder&);
    void remove_from_Message_locations();
    
    void addMsg(Message *m) { messages.insert(m); }
    void remMsg(Message *m) { messages.erase(m); }
};

class Message {
    friend class Folder;
    friend void swap(Message&, Message&);
    friend std::ostream &printMessage(std::ostream&, const Message&);
    
public:
    explicit Message(const std::string &str = "") : contents(str) { }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    
    void save(Folder&);
    void remove(Folder&);
    
private:
    std::string contents;
    std::set<Folder*> folders;
    
    void add_to_Folders(const Message&);
    void remove_from_Folders();
    
    // members to insert or remove a given Folder* into folders
    void addFolder(Folder *f) { folders.insert(f); }
    void remFolder(Folder *f) { folders.erase(f); }
};

Folder::Folder(const Folder &f)
{
    messages = f.messages;
    add_to_Message_locations(f);
}

Folder& Folder::operator=(const Folder &rhs)
{
    remove_from_Message_locations();
    messages = rhs.messages;
    add_to_Message_locations(rhs);
    return *this;
}

Folder::~Folder()
{
    remove_from_Message_locations();
}

void Folder::add_to_Message_locations(const Folder &f)
{
    for (auto m : f.messages)
        m->addFolder(this);
}

void Folder::remove_from_Message_locations()
{
    for (auto m : messages)
        m->remFolder(this);
    messages.clear();
}

void Folder::save(Message &m)
{
    messages.insert(&m);
    m.addFolder(this);
}

void Folder::remove(Message &m)
{
    messages.erase(&m);
    m.remFolder(this);
}

Message::Message(const Message &m)
{
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

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
    for (auto f : m.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
    folders.clear();
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

std::ostream &printMessage(std::ostream &os, const Message &m)
{
    os << m.contents << " ";
    for (const auto &e : m.folders) {
        std::cout << e << " ";
    } std::cout << std::endl;
    return os;
}

std::ostream &printFolder(std::ostream &os, Folder &f)
{
    for (const auto m : f.messages) {
        os << m << " ";
    } std::cout << std::endl;
    return os;
}

int main()
{
    std::cout << "Loading folders...\n";
    Folder drafts, deleted;
    
    std::cout << "Creating new message...\n";
    Message m1("manbearpig");
    
    printMessage(std::cout, m1);
    
    std::cout <<"\nSaving message to Drafts...\n";
    m1.save(drafts);
    std::cout << "There are " << drafts.size() << (drafts.size() == 1 ? " message" : " messages") << " in Drafts." << std::endl;
    
    std::cout <<"\nDeleting message from Drafts...\n";
    m1.save(deleted);
    m1.remove(drafts);
    std::cout << "There are now " << drafts.size() << (drafts.size() == 1 ? " message" : " messages") << " in Drafts." << std::endl;
    std::cout << "There " << (deleted.size() == 1 ? "is" : "are") <<  " also now " << deleted.size() << " deleted " << (deleted.size() == 1 ? "item" : "items") << " in the Deleted Items folder." << std::endl;
    
    return 0;
}
