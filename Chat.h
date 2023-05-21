//
// Chat.h
// 2023-05-21
// Ivan Konishchev
//

#pragma once
#include "DB.h"
#include <string>

class Chat
{
public:
    Chat();
    void reg(const std::string login,const std::string pass);
    bool login(const std::string login, const std::string pass);
    void deliteUser(const std::string &login);
private:
    DB data;
    int users_count;
    //void resize();
};