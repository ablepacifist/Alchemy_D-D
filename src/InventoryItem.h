#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <variant>
#include <string>
#include "Ingredient.h"
#include "Potion.h"

class InventoryItem {
public:
    InventoryItem(const Ingredient &ingredient, int quantity);
    InventoryItem(const Potion& potion, int quantity);

    bool isIngredient() const;
     bool isPotion() const;
    // Getters
    Potion getPotion() const;
    Ingredient getIngredient() const;
    int getQuantity() const;
    void display() const;
    std::string getName() const;
    // Method to update quantity
    void updateQuantity(int quantity);

    void decreaseQuantity(int amount);
    void updateEffects(const std::array<Effect, 4> &newEffects);

private:
    std::variant<Ingredient, Potion> item;
    int quantity;
};

#endif // INVENTORYITEM_H
