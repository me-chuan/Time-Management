#include "Utils.h"
#include <sstream>
#include <iomanip>

// 将时间字符串转换为 std::tm
std::tm stringToTime(const std::string& timeStr) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d_%H:%M");
    return tm;
}

// 将 std::tm 转换为 std::time_t
std::time_t tmToTimeT(const std::tm& tm) {
    return std::mktime(const_cast<std::tm*>(&tm));
}

std::string timeTToString(std::time_t timeT, const std::string& format) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format.c_str(), std::localtime(&timeT));
    return std::string(buffer);
}

std::time_t stringToTimeT(const std::string& timeStr, const std::string& format) {
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, format.c_str());
    return std::mktime(&tm);
}

bool isValidTimeFormat(const std::string& timeStr) {
    // 使用正则表达式验证时间格式
    std::regex timeRegex(R"(\d{4}-\d{2}-\d{2}_\d{2}:\d{2})");
    return std::regex_match(timeStr, timeRegex);
}