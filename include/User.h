#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(); // 默认构造函数
    User(const std::string& username, const std::string& password); // 用于注册时
    User(const std::string& username, const std::string& passwordHash, bool isHashed); // 用于加载哈希值

    bool authenticate(const std::string& username, const std::string& password) const;
    void setPassword(const std::string& password);
    std::string getUsername() const;
    std::string getPasswordHash() const;

private:
    std::string hashPassword(const std::string& password) const;

    std::string username;
    std::string password_hash;
};

#endif // USER_H