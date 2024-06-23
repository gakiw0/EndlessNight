#include "UserManager.hpp"

UserManager& UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

void UserManager::setUserId(const std::string& userId) {
    this->userId = userId;
}

std::string UserManager::getUserId() const {
    return userId;
}

void UserManager::setIdToken(const std::string& idToken) {
    this->idToken = idToken;
}

std::string UserManager::getIdToken() const {
    return idToken;
}

void UserManager::clear() {
    userId.clear();
    idToken.clear();
}
