//
// Created by simon on 23/05/2022.
//

#include <iostream>
#include "Log.h"
#include "InvalidFile.h"

const std::string Log::fileName = "log.txt";

std::string Log::GetStringLogType(LogType type) {

    switch (type) {
        case LogType::DEBUG:
            return "[DEBUG] ";
        case LogType::INFO:
            return "[INFO] ";
        case LogType::WARN:
            return "[WARN] ";
        case LogType::ERROR:
            return "[ERROR] ";
        default:
            std::cout << "napaka pri LogType!" << std::endl;
            return "";
    }
}

Log::Log(LogType type) {
    file.open(fileName, std::ios::app);

    if (file.is_open())
        file << GetStringLogType(type);

}

Log::~Log() {
    file.close();
}





