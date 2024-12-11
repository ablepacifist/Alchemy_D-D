#ifndef POTION_H
#define POTION_H

#include <array>
#include <string>
#include "Effect.h"

class Potion {
public:
    Potion(const std::string& name, const std::array<Effect, 4>& effects);

    std::string getName() const;
    std::array<Effect, 4> getEffects() const;
    void display() const;

private:
    std::string name;
    std::array<Effect, 4> effects;
};

#endif // POTION_H
