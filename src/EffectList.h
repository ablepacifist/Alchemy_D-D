#ifndef EFFECTLIST_H
#define EFFECTLIST_H

#include "Effect.h"
#include "Node.h"
#include <string>
#include <fstream>
#include <sstream>

class EffectList {
private:
    Node<Effect>* head;

public:
    EffectList() : head(nullptr) {}
    ~EffectList();

    void addEffect(const Effect& effect);
    void display() const;
    void loadFromFile(const std::string& filename);
    bool isFileEmpty(std::ifstream& file);
    Effect getEffectById(int id) const;
    Effect getEffectByName(const std::string& name) const;
    int getSize();
};

#endif

