#include "User.h"
#include <openssl/sha.h> // For SHA256 hashing
#include <sstream>
#include <iomanip>

const std::string SALT = "fixed_salt_value"; // 固定盐值

// 默认构造函数
User::User() : username(""), password_hash("") {}

// 用于注册时，哈希密码
User::User(const std::string& username, const std::string& password)
    : username(username), password_hash(hashPassword(password)) {}

// 用于加载哈希值
User::User(const std::string& username, const std::string& passwordHash, bool isHashed)
    : username(username), password_hash(passwordHash) {}


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
    // 确保盐值和密码拼接后没有多余字符
    std::string saltedPassword = SALT + password;

    // 使用 SHA256 生成哈希值
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(saltedPassword.c_str()), saltedPassword.size(), hash);

    // 将哈希值转换为十六进制字符串
    std::ostringstream oss;
    for (unsigned char byte : hash) {
        oss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }

    // 返回生成的哈希值
    return oss.str();
}

std::string User::getPasswordHash() const {
    return password_hash;
}
