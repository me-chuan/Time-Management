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
    if (!std::regex_match(timeStr, timeRegex)) {
        return false; // 格式不匹配
    }

    // 进一步解析时间字符串并检查值范围
    std::tm tm = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d_%H:%M");
    if (ss.fail()) {
        return false; // 解析失败
    }

    // 检查时间值范围
    if (tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mon > 11 || // 月份范围：0-11
        tm.tm_mday < 1 || tm.tm_mday > 31 ||                // 日期范围：1-31
        tm.tm_hour < 0 || tm.tm_hour > 23 ||                // 小时范围：0-23
        tm.tm_min < 0 || tm.tm_min > 59) {                  // 分钟范围：0-59
        return false; // 时间值超出范围
    }

    return true; // 时间格式和范围均有效
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}