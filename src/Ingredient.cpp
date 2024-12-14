#include "Ingredient.h"
#include <iostream>

//constructor
Ingredient::Ingredient(int ID, const std::string& name, const std::array<Effect, 4>& effects) : ID(ID), name(name), effects(effects) {}

// Getter for ID
int Ingredient::getID() const {
    return ID;
}

// Getter for Name
std::string Ingredient::getName() const {
    return name;
}

// Getter for Effects
std::array<Effect, 4> Ingredient::getEffects() const {
    return effects;
}
/*
std::array<Effect, 4>& Ingredient::getEffects() { 
    return effects;
}
*/
void Ingredient::learnEffect(int id, const std::string& name) {

    // Check if the effect is already learned
    for (const auto& effect : effects) {
        if (effect.getName() == name) {
            return;
        }
    }

    // Add the new effect if there's an empty slot
    for (int i = 0; i < 4; ++i) {
        if (effects[i].getName() == "NULL") {
            effects[i] = Effect(id, name);
            std::cout << "Effect " << name << " learned." << std::endl;
            return;
        }
    }

    std::cout << "No empty slots available to learn effect: " << name << std::endl;
}

// Method to display ingredient information
void Ingredient::display() const {
    std::cout << "Ingredient ID: " << ID << ", Name: " << name << std::endl;
    for (const auto& effect : effects) {
        effect.display();
    }
}
