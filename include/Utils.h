#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
#include <regex>

// 将时间字符串转换为 std::tm
std::tm stringToTime(const std::string& timeStr);

// 将 std::tm 转换为 std::time_t
std::time_t tmToTimeT(const std::tm& tm);

std::string timeTToString(std::time_t timeT, const std::string& format);

std::time_t stringToTimeT(const std::string& timeStr, const std::string& format);

bool isValidTimeFormat(const std::string& timeStr);

std::string trim(const std::string& str);

#endif // UTILS_H