//
// Created by simon on 25/04/2022.
//

#ifndef SIMONPLAZAR0801TEST_GRAPH_H
#define SIMONPLAZAR0801TEST_GRAPH_H

#include <string>
#include <sstream>
#include <utility>

class Graph {
private:
    unsigned int first;
    unsigned int second;
    std::string name;
public:
    Graph();

    Graph(unsigned int first, unsigned int second, std::string name);

    unsigned int getIx1() const;

    unsigned int getIx2() const;

    void setIx1(int ix1);

    void setIx2(int ix2);

    std::string toString() const;

    const std::string &getName() const;
};

Graph::Graph() : first(0), second(0), name("0") {}

Graph::Graph(unsigned int first, unsigned int second, std::string name) :
        first(first),
        second(second),
        name(std::move(name)) {}

unsigned int Graph::getIx1() const {
    return first;
}

unsigned int Graph::getIx2() const {
    return second;
}

void Graph::setIx1(int ix1) {
    Graph::first = ix1;
}

void Graph::setIx2(int ix2) {
    Graph::second = ix2;
}

std::string Graph::toString() const {
    std::stringstream ss;
    ss << name << std::endl;
    ss << first << " -> " << second;

    return ss.str();
}

const std::string &Graph::getName() const {
    return name;
}

#endif //SIMONPLAZAR0801TEST_GRAPH_H
