#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "IngredientList.h"
#include "EffectList.h"
#include "Inventory.h"
#include "Potion.h"
#include <filesystem>

namespace fs = std::filesystem;

class Player
{
private:
    int ID;
    int lvl;
    std::string name;
    EffectList effectList;         // Store EffectList inside Player
    IngredientList ingredientList; // Store IngredientList inside Player
    IngredientList masterList;
    Inventory inventory;
    void loadInventory(); // helper method
    void addPotionToInventory(const Potion &potion);
    void updateIngredientEffects(const Ingredient &ingredient, const std::array<Effect, 4> &newEffects);
    void updateInventoryItemEffects(InventoryItem* item, const std::array<Effect, 4>& newEffects);
    void eatUpdateInventoryItemEffects(InventoryItem* item, const std::array<Effect, 4>& newEffects);

public:
    Player(int ID, const std::string &name, IngredientList masterList);

    // Getters
    int getID() const;
    std::string getName() const;
    IngredientList &getIngredientList();             // Return a non-const reference for modification
    const IngredientList &getIngredientList() const; // Return a const reference for read-only access
    const Inventory &getInventory() const;

    // Methods
    void loadEffects();     //  load effects
    void loadIngredients(); // Method to load ingredients
    void saveIngredientList() const;
    void saveInventory() const;
    void display() const;
    void displayIngredients() const;
    // Inventory methods
    void addIngredientToInventory(const Ingredient &ingredient, int quantity);
    void displayInventory() const;
    void updateInventoryItemQuantity(const std::string &ingredientName, int quantity);
    void decreaseInventoryItemQuantity(const std::string &name);
    void increaseInventoryItemQuantity(const std::string name, int amount);
    //
    void forage();
    void eat(const std::string &IngredientName);
    void updatePlayerIngredientList(const std::string &ingredientName, const std::array<Effect, 4> &masterEffects);
    // potions:
    void createPotion(const std::string &ingredient1Name, const std::string &ingredient2Name);
    void combineIngredients(const std::string &ingredient1Name, const std::string &ingredient2Name);
};

#endif
