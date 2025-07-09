#include "User.h"
#include <openssl/sha.h> // For SHA256 hashing
#include <sstream>
#include <iomanip>

User::User(const std::string& username, const std::string& password)
    : username(username) {
    setPassword(password);
}

bool User::authenticate(const std::string& username, const std::string& password) const {
    return this->username == username && this->password_hash == hashPassword(password);
}

void User::setPassword(const std::string& password) {
    password_hash = hashPassword(password);
}

std::string User::getUsername() const {
    return username;
}

std::string User::hashPassword(const std::string& password) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return oss.str();
}