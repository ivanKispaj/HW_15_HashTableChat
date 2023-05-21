//
// DB.cpp
// 2023-05-21
// Ivan Konishchev
//

#include "DB.h"
DB::DB()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
DB::~DB()
{
    delete[] array;
}

void DB::add(const std::string &login, const std::string &pass)
{
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++)
    {
        index = hash_func(login, i);
        if (array[index].status == enPairStatus::free)
        {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size)
    {
        resize(i);
        add(login, pass);
        return;
    }

    // кладем в свободную ячейку пару
    array[index] = Pair(login, hashForPassword(pass));
    count++;
}

// void DB::add(const std::string &login, int pass)
// {
//     int index = -1, i = 0;
//     // берем пробы по всем i от 0 до размера массива
//     for (; i < mem_size; i++)
//     {
//         index = hash_func(login, i);
//         if (array[index].status == enPairStatus::free)
//         {
//             // найдена пустая ячейка, занимаем ее
//             break;
//         }
//     }
//     if (i >= mem_size)
//     {
//         resize(i);
//         add(login, pass);
//         return;
//     }

//     // кладем в свободную ячейку пару
//     array[index] = Pair(login, pass);
//     count++;
// }

int DB::hash_func(std::string login, int offset)
{
    // вычисляем индекс
    int sum = 0, i = 0;
    for (; i < login.length(); i++)
    {
        sum += login[i];
    }
    // линейные пробы
    return (sum % mem_size + offset) % mem_size;
}

void DB::del(const std::string &login)
{
    int index = -1, i = 0;

    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++)
    {
        index = hash_func(login, i);
        if (array[index].user_name == login)
        {
            array[index] = Pair();
            array[index].status = enPairStatus::deleted;
        }
    }
}

bool DB::auth(const std::string &login, const std::string &pass)
{
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++)
    {
        index = hash_func(login, i);
        if (array[i].user_name == login)
        {
            std::string hashPass = hashForPassword(pass);
            if (array[i].password == hashPass)
            {
                return true;
            }
        }
    }

    return false;
}

void DB::resize(int cur)
{
    Pair *save_ct = array; // запоминаем старый массив
    int oldSize = mem_size;
    if (cur > mem_size * 2)
    {
        mem_size = cur * 2;
    }
    else
    {
        mem_size *= 2; // увеличиваем размер в два раза
    }
    count = 0; // обнуляем количество элементов
    array = new Pair[mem_size];
    for (int i = 0; i < mem_size; i++)
    {
        array[i] = Pair();
    }

    for (int i = 0; i < oldSize; i++)
    {
        // перебираем все старые цепочки
        Pair current = save_ct[i];
        // пересчитываем хеши и добавляем в новый массив
        add(current.user_name, current.password);
    }

    delete[] save_ct;
}

std::string DB::hashForPassword(const std::string &pass)
{
    std::string hash;
    char temp[pass.size()];
    int N = 13, k = 0;
    double A = 0.618033;

    for (int i = 0; i < pass.length(); i++)
    {
        k += int(pass[i]);
        int h = N * fmod(k * A, 1);

        temp[i] = char(h + '!');
    }

    temp[pass.length() - 1] = '\0';
    return hash.append(temp);
}