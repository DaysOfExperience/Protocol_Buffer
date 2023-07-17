#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;
void AddPeopleInfo(contacts::PeopleInfo *ptr)
{
    std::string name;
    int age;

    std::cout << "请输入新增联系人的姓名" << std::endl;
    std::getline(cin, name);
    ptr->set_name(name);

    std::cout << "请输入新增联系人的年龄" << std::endl;
    std::cin >> age;
    ptr->set_age(age);
    cin.ignore(256, '\n');
    for(int i = 0; ; ++i) {
        std::string number;
        std::cout << "请输入新增联系人的联系方式"<<i+1<<"（只输入回车表示完成电话新增）" << std::endl;
        std::getline(cin, number);
        if(number.empty()) break;
        contacts::PeopleInfo_Phone* phone = ptr->add_phone();
        phone->set_number(number);
    }
}

int main()
{
    contacts::Contacts contacts;
    fstream input("contacts_file", ios::in | ios::binary);
    if(!input) {
        cout << "File not found, create a new file" << endl;
    }
    else if(!contacts.ParseFromIstream(&input)) {
        cerr << "Failed to parse contacts" << endl;
        input.close();
        return -1;
    }

    // 目前已经反序列化成功，在contacts中（可能没有联系人，因为contacts_file可能是空的）
    AddPeopleInfo(contacts.add_contacts());  // contacts::PeopleInfo*

    // 向磁盘⽂件写⼊新的 contacts
    fstream output("contacts_file", ios::out | ios::binary | ios::trunc);
    if(!contacts.SerializeToOstream(&output)) {
        std::cout << "Failed to serialize to file" << std::endl;
        input.close();
        output.close();
        return -1;
    }
    std::cout << "serialize contacts success" << std::endl;
    input.close();
    output.close();
    return 0;
}