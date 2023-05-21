//
// Chat.cpp
// 2023-05-21
// Ivan Konishchev
//

#include "Chat.h"
#include "iostream"
#include "string.h"

Chat::Chat()
{
    users_count = 0;
}
void Chat::reg(const std::string login, const std::string pass)
{
    data.add(login,pass);
    users_count++;
}
bool Chat::login(const std::string login, const std::string pass)
{
   return data.auth(login,pass);
}

void Chat::deliteUser(const std::string &login)
{
    data.del(login);
    users_count--;
}