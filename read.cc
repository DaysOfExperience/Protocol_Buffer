#include <iostream>
#include <fstream>
#include "contacts.pb.h"

void PrintContacts(const contacts::Contacts &contacts)
{
    for(int i = 0; i < contacts.contacts_size(); ++i) {
        std::cout << "person" << i+1 << std::endl;
        const contacts::PeopleInfo& people = contacts.contacts(i);
        std::cout << "name: " << people.name()
                << " age: " << people.age() << std::endl;
        for(int j = 0; j < people.phone_size(); ++j) {
            contacts::PeopleInfo_Phone phone = people.phone(j);
            std::cout << "phone" << j+1 << ": " << phone.number()
                << "(" << phone.PhoneType_Name(phone.type()) << ")" << std::endl;
        }
    }
}

int main()
{
    contacts::Contacts contacts;
    std::fstream input("contacts_file", std::ios::in | std::ios::binary);
    if(!contacts.ParseFromIstream(&input)) {
        std::cout << "parse failed" << std::endl;
        input.close();
        return -1;
    }
    PrintContacts(contacts);
    input.close();
    return 0;
}