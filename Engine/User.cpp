#include "User.hpp"

#include <string>
// コンストラクタ
User::User() : name(""), password(""), time(0), money(0) {}

// ゲッターとセッター
std::string User::getName() const
{
    return name;
}

void User::setName(std::string name)
{
    this->name = name;
}

std::string User::getPassword() const
{
    return password;
}

void User::setPassword(std::string pwd)
{
    this->password = pwd;
}

int User::getTime() const
{
    return time;
}

void User::setTime(int t)
{
    this->time = t;
}

int User::getMoney() const
{
    return money;
}

void User::setMoney(int m)
{
    this->money = m;
}

int User::getScore() const
{
    return score;
}

void User::setScore(int s)
{
    this->score = s;
}

User &User::getInstance()
{
    static User instance;
    return instance;
}

bool User::operator==(const User &other) const
{
    return name == other.name && password == other.password;
}