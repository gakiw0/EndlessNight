#include "FirebaseAuth.hpp"
#include <curl/curl.h>
#include <sstream>
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}

FirebaseAuth::FirebaseAuth() {
}

FirebaseAuth::~FirebaseAuth() {
}

std::string FirebaseAuth::makeHttpRequest(const std::string& url, const std::string& jsonPayload) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L); // POSTリクエストを明示的に設定

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    return readBuffer;
}

std::string FirebaseAuth::extractJsonValue(const std::string& json, const std::string& key) {
    size_t keyPos = json.find("\"" + key + "\"");
    if (keyPos == std::string::npos) return "";

    size_t valueStart = json.find(":", keyPos) + 1;
    size_t valueEnd = json.find_first_of(",}", valueStart);

    if (json[valueStart] == '\"') valueStart++;
    if (json[valueEnd - 1] == '\"') valueEnd--;

    return json.substr(valueStart, valueEnd - valueStart);
}

std::string FirebaseAuth::signIn(const std::string& email, const std::string& password) {
    std::string url = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + apiKey;
    std::stringstream jsonPayload;
    jsonPayload << "{\"email\":\"" << email << "\",\"password\":\"" << password << "\",\"returnSecureToken\":true}";

    std::string response = makeHttpRequest(url, jsonPayload.str());
    idToken = extractJsonValue(response, "idToken");
    return response;
}

std::string FirebaseAuth::registerUser(const std::string& email, const std::string& password) {
    std::string url = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + apiKey;
    std::stringstream jsonPayload;
    jsonPayload << "{\"email\":\"" << email << "\",\"password\":\"" << password << "\",\"returnSecureToken\":true}";

    return makeHttpRequest(url, jsonPayload.str());
}

std::string FirebaseAuth::logoutUser(const std::string& idToken) {
    // Firebaseには直接的なログアウトAPIはありません。
    this->idToken.clear();
    return "{}";
}
