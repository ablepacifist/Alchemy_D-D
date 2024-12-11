#include "InventoryItem.h"

#include "InventoryItem.h"
#include <iostream>

InventoryItem::InventoryItem(const Ingredient &ingredient, int quantity) : item(ingredient), quantity(quantity) {}
InventoryItem::InventoryItem(const Potion &potion, int quantity) : item(potion), quantity(quantity) {}

bool InventoryItem::isIngredient() const
{
    return std::holds_alternative<Ingredient>(item);
}

bool InventoryItem::isPotion() const
{
    return std::holds_alternative<Potion>(item);
}

Ingredient InventoryItem::getIngredient() const
{
    return std::get<Ingredient>(item);
}

Potion InventoryItem::getPotion() const
{
    return std::get<Potion>(item);
}

std::string InventoryItem::getName() const
{
    if (isIngredient())
    {
        return getIngredient().getName();
    }
    else
    {
        return getPotion().getName();
    }
}

void InventoryItem::display() const
{
    if (isIngredient())
    {
        getIngredient().display();
    }
    else
    {
        getPotion().display();
    }
}

int InventoryItem::getQuantity() const
{
    return quantity;
}

// Method to update quantity
void InventoryItem::updateQuantity(int quantity)
{
    this->quantity = quantity;
}
void InventoryItem::decreaseQuantity(int amount)
{
    this->quantity = quantity - amount;
}
void InventoryItem::updateEffects(const std::array<Effect, 4> &newEffects)
{
    if (isIngredient())
    {
        Ingredient &ingredient = std::get<Ingredient>(item);
        for (const auto &newEffect : newEffects)
        {
            if (newEffect.isValid())
            {
                ingredient.learnEffect(newEffect.getID(), newEffect.getName());
            }
        }
    }
}