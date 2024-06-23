#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <string>

class UserManager {
public:
    static UserManager& getInstance();

    void setUserId(const std::string& userId);
    std::string getUserId() const;

    void setIdToken(const std::string& idToken);
    std::string getIdToken() const;

    void clear();

private:
    std::string userId;
    std::string idToken;

    UserManager() = default;
    ~UserManager() = default;
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;
};

#endif // USERMANAGER_HPP
