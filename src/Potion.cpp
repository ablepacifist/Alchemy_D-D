#include "Potion.h"
#include <iostream>

Potion::Potion(const std::string& name, const std::array<Effect, 4>& effects)
    : name(name), effects(effects) {}

std::string Potion::getName() const {
    return name;
}

std::array<Effect, 4> Potion::getEffects() const {
    return effects;
}

void Potion::display() const {
    std::cout << "Potion Name: " << name << std::endl;
    for (const auto& effect : effects) {
        effect.display();
    }
}
