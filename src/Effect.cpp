#include "Effect.h"
#include <iostream>
//defult constructor:
//Effect::Effect() : ID(0), name("") {}
// Constructor
Effect::Effect(int ID, const std::string& name) : ID(ID), name(name) {}

// Getter for ID
int Effect::getID() const {
    return ID;
}

// Getter for Name
std::string Effect::getName() const {
    return name;
}

//display the effect information
void Effect::display() const {
    std::cout << "Effect ID: " << ID << ", Name: " << name << std::endl;
}
bool Effect::isValid() const {
     return !name.empty(); // or any other condition that determines validity
      }
