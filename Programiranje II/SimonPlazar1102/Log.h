//
// Created by simon on 23/05/2022.
//

#ifndef SIMONPLAZAR1102_LOG_H
#define SIMONPLAZAR1102_LOG_H

#include <fstream>

enum class LogType {
    DEBUG, INFO, WARN, ERROR
};

class Log {
private:
    std::ofstream file;
    const static std::string fileName;
public:
    static std::string GetStringLogType(LogType type);

    explicit Log(LogType type);

    ~Log();

    template<typename T>
    Log &operator<<(const T &msg) {
        if (file.is_open())
            file << msg;

        return *this;
    }
};


#endif //SIMONPLAZAR1102_LOG_H
