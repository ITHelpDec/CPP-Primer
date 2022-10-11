// Message

#include <string>
#include <set>
#include <iostream>

class Message;

class Folder {
    friend class Message;
    friend void swap(Message&, Message&);
    friend void swap(Folder &lhs, Folder &rhs);
    friend std::ostream &printFolder(std::ostream&, Folder&);
    
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    
    // move constructor and move-assignment operator
    Folder(Folder &f) : messages(f.messages) { move_Messages(&f); }
    Folder& operator=(Folder&&);
    
    void save(Message&);
    void remove(Message&);
    
    std::size_t size() { return messages.size(); }
    
private:
    std::set<Message*> messages;
    
    void add_to_Message_locations(const Folder&);
    void remove_from_Message_locations();
    
    void addMsg(Message *m) { messages.insert(m); }
    void remMsg(Message *m) { messages.erase(m); }
    
    // might be worth creating helper utility function in Folders class
    void move_Messages(Folder*);
};

class Message {
    friend class Folder;
    friend void swap(Message&, Message&);
    friend void swap(Folder &lhs, Folder &rhs);
    friend std::ostream &printMessage(std::ostream&, const Message&);
    
public:
    explicit Message(const std::string &str = "") : contents(str) { }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    
    // move constructor
    Message(Message &&m) : contents(std::move(m.contents))
    {
        move_Folders(&m);
    }
    // move-assingment operator
    Message& operator=(Message&&);
    
    void save(Folder&);
    void remove(Folder&);
    
private:
    std::string contents;
    std::set<Folder*> folders;
    
    void add_to_Folders(const Message&);
    void remove_from_Folders();
    
    void addFolder(Folder *f) { folders.insert(f); }
    void remFolder(Folder *f) { folders.erase(f); }
    
    // creating utility function for move constructor and move-assignment operator
    void move_Folders(Message*);
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

void swap(Message &lhs, Message &rhs)
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

void swap(Folder &lhs, Folder &rhs)
{
    using std::swap;
    
    for (auto m : lhs.messages)
        m->remFolder(&lhs);
    for (auto m : rhs.messages)
        m->remFolder(&rhs);
    
    swap(lhs.messages, rhs.messages);
    
    for (auto m : lhs.messages)
        m->addFolder(&lhs);
    for (auto m : rhs.messages)
        m->addFolder(&rhs);
}

// move the Folder pointers from m to this Message
void Message::move_Folders(Message *m)
{
    // uses set move assignment
    folders = std::move(m->folders);
    
    // for each Folder
    for (auto f : folders) {
        // remove the old Message from the Folder
        f->remMsg(m);
        // add this Message to that Folder
        f->addMsg(this);
    }
    // ensure that destorying m is harmless
    m->folders.clear();
}

// move-assignment operator
Message& Message::operator=(Message &&rhs)
{
    // direct check for self-assignment
    if (this != &rhs) {
        // clear lhs to make way for rhs move
        remove_from_Folders();
        contents = std::move(rhs.contents);
        // reset the Folders to point the this message
        move_Folders(&rhs);
    }
    return *this;
}

// move the Message pointers from f to this Folder
void Folder::move_Messages(Folder *f)
{
    // mvoe contents
    messages = std::move(f->messages);
    // go through each message, removing old folders before adding new ones
    for (auto m : messages) {
        m->remFolder(f);
        m->addFolder(this);
    }
    // make f->messages destructable
    f->messages.clear();
}

// move-assignment operator
Folder& Folder::operator=(Folder &&rhs)
{
    if (this != &rhs) {
        remove_from_Message_locations();
        messages = std::move(rhs.messages);
        move_Messages(&rhs);
    }
    return *this;
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
    Message m1("manbearpig");
    std::cout << "m1 = "; printMessage(std::cout, m1);
    
    Message m2("supercereal");
    std::cout << "m2 = ";  printMessage(std::cout, m2);
   
    std::cout << "\nMoving m1 to m3...\n";
    Message m3(std::move(m1));
    std::cout << "m3 = "; printMessage(std::cout, m3);
    
    std::cout << "\nMove-assigning m2 to m3...\n";
    m3 = std::move(m2);
    std::cout << "m3 = "; printMessage(std::cout, m3);
    
    std::cout << "\nPrinting out final results...\n";
    std::cout << "m1 = "; printMessage(std::cout, m1);
    std::cout << "m2 = "; printMessage(std::cout, m2);
    std::cout << "m3 = "; printMessage(std::cout, m3);
    
    return 0;
}
