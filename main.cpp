// 
// main.cpp
// 2023-05-21
// Ivan Konishchev
//


#include<iostream>
#include "Chat.h"

int main(int argc, const char *argv[])
{
    Chat chat;
    chat.reg("kispaj","Pass");
    chat.reg("kispaj1","1234");
    chat.reg("kispaj2","5314214");
    chat.reg("qwertyuiopasdfghjkl","qwertY");
    chat.deliteUser("kispaj2");
    chat.login("kispaj","pass") ? std::cout << "Sacces\n" : std::cout << "Fail!\n";
    return 0;
}