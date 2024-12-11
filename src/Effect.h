#ifndef EFFECT_H
#define EFFECT_H

#include <string>

class Effect{
    private:
    int ID;
    std::string name;
    public:
    Effect() : ID(0), name("") {}
    Effect(int ID, const std::string& name);
    //getters
    int getID() const;
    std::string getName() const;
    //other
    void display() const;
    bool isValid() const;
};

#endif