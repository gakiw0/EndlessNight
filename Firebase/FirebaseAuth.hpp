#ifndef FIREBASEAUTH_HPP
#define FIREBASEAUTH_HPP

#include <string>

class FirebaseAuth {
public:
    FirebaseAuth();
    ~FirebaseAuth(); // デストラクタを追加
    std::string signIn(const std::string& email, const std::string& password);
    std::string registerUser(const std::string& email, const std::string& password);
    std::string logoutUser(const std::string& idToken);
    std::string getIdToken() const { return idToken; }

private:
    std::string apiKey = "AIzaSyBE66TeoDe2vYlYHpzmIp-mmAVhtUytoAo";
    std::string idToken;
    std::string makeHttpRequest(const std::string& url, const std::string& jsonPayload);
    std::string extractJsonValue(const std::string& json, const std::string& key);
};

#endif // FIREBASEAUTH_HPP
