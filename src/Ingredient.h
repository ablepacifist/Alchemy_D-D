#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <array>
#include "Effect.h"

class Ingredient {
public:
    // Constructor
    Ingredient(int ID, const std::string& name, const std::array<Effect, 4>& effects);

    // Getters
    int getID() const;
    std::string getName() const;
    std::array<Effect, 4> getEffects() const;

    // Setters
    void learnEffect(int id,const std::string& name);

    // Method to display ingredient information
    void display() const;

private:
    int ID;
    std::string name;
    std::array<Effect, 4> effects;
};

#endif // INGREDIENT_H
