#include <iostream>
#include <fstream>
#include "contacts.pb.h" // 这里面其实就是协议的结构体，包含序列化，设置字段值等等...

int main()
{
    // .proto⽂件声明的package，通过protoc编译后，会为编译⽣成的C++代码声明同名的命名空间
    contacts::PeopleInfo people;
    people.set_name("李狗");
    people.set_age(20);
    std::string str;
    // 调⽤序列化⽅法，将序列化后的⼆进制序列存⼊string中
    if (!people.SerializeToString(&str))
    {
        std::cout << "序列化people失败" << std::endl;
        return -1;
    }
    std::cout << "people序列化之后的结果为: " << str << std::endl;

    contacts::PeopleInfo people2;
    // 调⽤反序列化⽅法，读取string中存放的⼆进制序列，并反序列化出对象
    if (!people2.ParseFromString(str))
    {
        std::cout << "反序列化失败" << std::endl;
        return -1;
    }
    std::cout << "反序列化成功, people name: " << people2.name() << " people age: " << people2.age()
              << std::endl;

    return 0;
}