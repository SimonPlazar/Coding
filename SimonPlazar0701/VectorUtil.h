//
// Created by simon on 15/04/2022.
//

#ifndef SIMONPLAZAR0701_VECTORUTIL_H
#define SIMONPLAZAR0701_VECTORUTIL_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Speakers.h"

template<typename T>
std::vector<T> mergeLists(const std::vector<std::vector<T>> &vec) {
    std::vector<T> output;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            output.push_back(vec[i][j]);
        }
    }
    return output;
}

std::string mergeLists(const std::vector<std::string>& vec) {
    std::string output;
    for (auto & string : vec) {
        output += string + " ";
    }
    return output;
}

static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char randomChar(){
    return alphanum[rand() % stringLength];
}

double randomDouble() {
    //random double from 0-1
    return ((double) rand()) / ((double) RAND_MAX);
}

double randomDoubleInterval(double start, double end) {
    //random number on a given interval
    return randomDouble() * (end - start) + start;
}

double decimalPlaces(double number, int decimals) {
    //trunc rounds to the closest integer
    return trunc(number * pow(10, decimals)) / pow(10, decimals);
}


std::string randString(int size){
    std::string string;
    for (int i = 0; i < size; ++i) {
        string += randomChar();
    }
    return string;
}

template<int N, typename T>
void fillDefault(std::vector<T> &vec) {
    std::cout<<"Default\n";
    for (int i = 0; i < N; ++i) {
        vec.push_back(T());
    }
}

template<typename T>
std::string toString(std::vector<T> vec) {
    std::stringstream ss;

    for (int i = 0; i < vec.size(); ++i) {
        ss << vec[i].toString();
    }

    return ss.str();
}

template<typename T>
void print(std::vector<T> vec) {
    std::cout << toString(vec);
    std::cout << std::endl;
}

template<typename T>
std::vector<T> reverse(std::vector<T> vec) {
    int size = vec.size();
    std::vector<T> tmp(size);

    for (int i = 0; i < size; ++i) {
        tmp[i] = vec[size-i-1];
    }

    return tmp;
}

template<int N>
void fillDefault(std::vector<Speakers> &vec) {
    std::cout<<"Special\n";
    for (int i = 0; i < N; ++i) {
        vec.emplace_back(randString(6), decimalPlaces(randomDoubleInterval(2.5,8.2),2));
    }
}

#endif //SIMONPLAZAR0701_VECTORUTIL_H
