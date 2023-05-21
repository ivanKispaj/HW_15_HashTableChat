//
// DB.h
// 2023-05-21
// Ivan Konishchev
//

#pragma once

#include <string>
#include <iostream>

// #define NAMELENGTH 10 // Зафикcируем длину имени

// typedef char Login[NAMELENGTH]; // тип имя фрукта

class DB
{ // хэш таблица
public:
    DB();
    ~DB();
    void add(const std::string &login, const std::string &pass);
    void del(const std::string &login);
    bool auth(const std::string &login, const std::string &pass);

    // void dummy(char *fr_name);

private:
    enum enPairStatus
    {
        free,
        engaged,
        deleted
    };

    struct Pair
    { // пара ключ-значение

        Pair() : user_name(""),
                 password(""),
                 status(enPairStatus::free)
        {
        }
        Pair(std::string login, std::string pass) : user_name(login), password(pass),
                                            status(enPairStatus::engaged) {}

        // Pair &operator=(const Pair &other)
        // {
        //     password = other.password;
        //     // memcpy(user_name, other.user_name, NAMELENGTH);
        //     status = other.status;

        //     return *this;
        // }

        // bool operator==(const Pair &other)
        // {
        //     return status == other.status &&
        //            (status != enPairStatus::engaged || (password == other.password && !strcmp(user_name, other.user_name)));
        // }

        std::string user_name;
        std::string password;

        enPairStatus status;
    };

    int hash_func(std::string login, int offset);
    //void add(const std::string &login, int pass);
    std::string hashForPassword(const std::string &pass);
    Pair *array;
    void resize(int cur);

    int mem_size;
    int count;
};