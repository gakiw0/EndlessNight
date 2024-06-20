#ifndef USER_HPP
#define USER_HPP

#include <vector>
#include <string>

class User
{
private:
    std::string name;
    std::string password;
    int time;
    int money;
    int score;

public:
    User();
    std::string getName() const;
    void setName(std::string name);
    std::string getPassword() const;
    void setPassword(std::string pwd);
    int getTime() const;
    void setTime(int t);
    int getMoney() const;
    void setMoney(int m);
    int getScore() const;
    void setScore(int s);
    static User &getInstance();
    bool operator==(const User &otheer) const;
}; 

#endif // USER_HPP

