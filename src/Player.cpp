#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

Player::Player(int ID, const std::string &name, IngredientList masterList) : ID(ID), name(name), masterList(masterList)
{
    loadEffects();     // Load effects first
    loadIngredients(); // Then load ingredients
    loadInventory();   // load inventory from file
}

// Getters
int Player::getID() const
{
    return ID;
}

std::string Player::getName() const
{
    return name;
}
IngredientList &Player::getIngredientList()
{
    return ingredientList;
}

const IngredientList &Player::getIngredientList() const
{
    return ingredientList;
}
const Inventory &Player::getInventory() const
{
    return inventory;
}

// Method to load effects from file
void Player::loadEffects()
{
    // Construct the path to the data folder relative to the current path
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path effectsFilePath = fs::absolute(dataPath / "effects.txt");
    effectList.loadFromFile(effectsFilePath.string());

    std::cout << "Effects loaded for player " << name << std::endl;
}

// Method to load ingredients from file
void Player::loadIngredients()
{
    // Construct the path to the data folder relative to the current path
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path ingredientFilePath = fs::absolute(dataPath / (name + "_ingredient_list.txt"));

    if (!fs::exists(ingredientFilePath))
    {
        std::cerr << "Error: File does not exist " << ingredientFilePath << std::endl;
        return;
    }

    std::ifstream file(ingredientFilePath.string());
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << ingredientFilePath << std::endl;
        return;
    }

    ingredientList.loadFromFile(ingredientFilePath.string(), effectList); // Pass by value
    std::cout << "Ingredients loaded for player " << name << std::endl;
}

void Player::loadInventory()
{
    // Construct the path to the data folder relative to the current path
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path inventoryFilePath = fs::absolute(dataPath / (name + "_inventory.txt"));
    std::cout << "Reading file: " << inventoryFilePath << std::endl;
    inventory.loadFromFile(inventoryFilePath.string(), ingredientList);
}
void Player::addIngredientToInventory(const Ingredient &Ingredient, int amount)
{
    InventoryItem *item = inventory.findItemByName(Ingredient.getName());
    if (item)
    {
        item->updateQuantity(item->getQuantity() + amount);
    }
    else
    {
        inventory.addItem(InventoryItem(Ingredient, amount));
    }
}

// Saving methods:

// Method to save ingredient list to a file
void Player::saveIngredientList() const
{
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path ingredientListPath = fs::absolute(dataPath / (name + "_ingredient_list.txt"));

    std::ofstream file(ingredientListPath.string());

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << ingredientListPath << std::endl;
        return;
    }

    Node<Ingredient> *current = ingredientList.getHead();
    while (current != nullptr)
    {
        file << current->data.getName();

        const auto &effects = current->data.getEffects();
        for (const auto &effect : effects)
        {
            file << ",";
            if (effect.isValid())
            {
                file << effect.getName();
            }
            else
            {
                file << "NULL";
            }
        }
        file << std::endl;
        current = current->next;
    }

    file.close();
    std::cout << "Ingredient list saved to " << ingredientListPath << std::endl;
}

void Player::saveInventory() const
{
    // Construct the path to the data folder relative to the current path
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path inventoryPath = fs::absolute(dataPath / (name + "_inventory.txt"));
    inventory.saveToFile(inventoryPath.string());
}
// Display methods

// Method to display player info
void Player::display() const
{
    std::cout << "Player name: " << name << std::endl;
    std::cout << "Player ID: " << ID << std::endl;
}

// Method to display ingredients
void Player::displayIngredients() const
{
    ingredientList.display();
}
// Method to display player's inventory
void Player::displayInventory() const
{
    std::cout << "Inventory for " << name << ":" << std::endl;
    inventory.display();
}
// other functions:

// potions:

void Player::combineIngredients(const std::string &ingredient1Name, const std::string &ingredient2Name)
{
    Ingredient *ingredient1 = masterList.getByName(ingredient1Name);
    Ingredient *ingredient2 = masterList.getByName(ingredient2Name);
    std::cout << "the two ingredients are:" << ingredient1->getName() << " , " << ingredient2->getName() << std::endl;
    if (ingredient1 == nullptr || ingredient2 == nullptr)
    {
        std::cerr << "One or both ingredients not found in inventory or quantity is zero." << std::endl;
        return;
    }

    // Decrease the quantity of the ingredients by 1
    InventoryItem *ingredient1Item = inventory.findItemByName(ingredient1Name);
    InventoryItem *ingredient2Item = inventory.findItemByName(ingredient2Name);
    ingredient1Item->decreaseQuantity(1);
    ingredient2Item->decreaseQuantity(1);
    std::cout << "consumed: " << ingredient1Item->getName() << " and " << ingredient2Item->getName() << std::endl;

    std::array<Effect, 4> potionEffects = {Effect(), Effect(), Effect(), Effect()};
    size_t effectIndex = 0;

    // Check for matching effects using the master list
    for (const auto &effect1 : ingredient1->getEffects())
    {
        for (const auto &effect2 : ingredient2->getEffects())
        {
            if (effect1.getName() == effect2.getName())
            {
                std::cout << "got matching effects: " << effect1.getName() << " and " << effect2.getName() << std::endl;
                if (effectIndex < potionEffects.size())
                {
                    potionEffects[effectIndex++] = effect1;
                }
            }
        }
    }
    // fill in the rest of the effects with "NULL"
    for (int i = effectIndex; i < 4; i++)
    {
        potionEffects[i] = effectList.getEffectByName("NULL");
    }
    // Create potion if there are matching effects
    if (effectIndex > 0)
    {
        // Construct the potion name based on the effects
        std::string potionName = "Potion of ";
        for (size_t i = 0; i < effectIndex; ++i)
        {
            if (i > 0)
            {
                potionName += " and ";
            }
            potionName += potionEffects[i].getName();
        }
        std::cout << "new potion to be created: " << potionName << std::endl;
        Potion newPotion(potionName, potionEffects);
        std::cout << "new potion was created: " << newPotion.getName() << std::endl;
        addPotionToInventory(newPotion);
        updateIngredientEffects(*ingredient1, potionEffects);
        updateIngredientEffects(*ingredient2, potionEffects);
        //
        updateInventoryItemEffects(ingredient1Item, potionEffects);
        updateInventoryItemEffects(ingredient2Item, potionEffects);
        std::cout << "Potion created and added to inventory." << std::endl;
    }
    else
    {
        std::cerr << "No matching effects found between the ingredients." << std::endl;
    }
}

void Player::addPotionToInventory(const Potion &potion)
{
    std::cout << "trying to add potion to inventory: " << potion.getName() << std::endl;
    inventory.addItem(InventoryItem(potion, 1));
}

void Player::updateIngredientEffects(const Ingredient &ingredient, const std::array<Effect, 4> &newEffects)
{
    std::cout << "Updating effects for ingredient: " << ingredient.getName() << std::endl;

    Ingredient *playerIngredient = ingredientList.getByName(ingredient.getName());
    if (playerIngredient != nullptr)
    {
        bool updated = false;

        for (const auto &newEffect : newEffects)
        {
            if (!(newEffect.getName() == "NULL"))
            {
                playerIngredient->learnEffect(newEffect.getID(), newEffect.getName());
                updated = true;
            }
        }

        if (updated)
        {
            std::cout << "Effects updated for ingredient: " << ingredient.getName() << std::endl;
        }
        else
        {
            std::cout << "No available slots to update effects for ingredient: " << ingredient.getName() << std::endl;
        }
    }
    else
    {
        std::cerr << "Ingredient not found in player's ingredient list: " << ingredient.getName() << std::endl;
    }
}
void Player::updateInventoryItemEffects(InventoryItem* item, const std::array<Effect, 4>& newEffects) {
    if (item->isIngredient()) {
        std::cout << "Updating effects for inventory item: " << item->getName() << std::endl;
        item->updateEffects(newEffects);
        std::cout << "Effects updated for inventory item: " << item->getName() << std::endl;
    }
}


// Function to eat an ingredient
void Player::eat(const std::string &ingredientName)
{
    std::cout << "Starting eat process for " << ingredientName << std::endl;

    // Check if the item is in the inventory and has quantity > 0
    InventoryItem *item = inventory.findItemByName(ingredientName);
    if (item && item->getQuantity() > 0)
    {
        item->decreaseQuantity(1);
        std::cout << "Consumed one " << ingredientName << ". Remaining: " << item->getQuantity() << std::endl;
    }
    else
    {
        std::cerr << "Ingredient " << ingredientName << " not found in inventory or quantity is zero." << std::endl;
        return;
    }

    // Find the ingredient in the master list to get its effects
    std::cout << "Looking up ingredient in master list..." << std::endl;
    Ingredient *masterIngredient = masterList.getByName(ingredientName);
    if (masterIngredient != nullptr)
    {
        auto masterEffects = masterIngredient->getEffects();
        std::cout << "Master ingredient found. Updating player ingredient list..." << std::endl;
        updatePlayerIngredientList(ingredientName, masterEffects);
        eatUpdateInventoryItemEffects(item, masterEffects);
        std::cout << "Finished eat process for " << ingredientName << std::endl;
    }
    else
    {
        std::cerr << "Ingredient " << ingredientName << " not found in master list." << std::endl;
    }
}
void Player::eatUpdateInventoryItemEffects(InventoryItem* item, const std::array<Effect, 4>& masterEffects) {
    std::array<Effect, 4> newEffects;
    bool learnOne = false;

    for(int i = 0; i < 4; ++i) {
        if (!(item->getIngredient().getEffects()[i].getName() == "NULL")) {
            newEffects[i] = item->getIngredient().getEffects()[i];
        } else if (item->getIngredient().getEffects()[i].getName() == "NULL" && !learnOne) {
            newEffects[i] = masterEffects[i];
            learnOne = true;
        } else {
            newEffects[i] = Effect(45, "NULL");
        }
    }

    // Now call updateInventoryItemEffects with the new effects
    item->updateEffects(newEffects);
}


void Player::updatePlayerIngredientList(const std::string &ingredientName, const std::array<Effect, 4> &masterEffects)
{
    std::cout << "Updating player ingredient list for " << ingredientName << std::endl;
    Ingredient *playerIngredient = ingredientList.getByName(ingredientName);
    if (playerIngredient != nullptr)
    {
        std::cout << "Player ingredient found. Checking effects..." << std::endl;
        auto playerEffects = playerIngredient->getEffects();
        for (size_t i = 0; i < playerEffects.size(); ++i)
        {
            std::cout << "Checking effect at index " << i << ": " << playerEffects[i].getName() << std::endl;
            if (playerEffects[i].getName() == "NULL")
            {
                std::cout << "Found NULL effect at index " << i << ". Replacing with effect from master list..." << std::endl;
                playerIngredient->learnEffect(masterEffects[i].getID(), masterEffects[i].getName());
                std::cout << "Updated effect for " << ingredientName << ": " << playerIngredient->getEffects()[i].getName() << std::endl;
                return;
            }
        }
        std::cerr << "All effect slots are full for ingredient: " << ingredientName << std::endl;
    }
    else
    {
        std::cerr << "Ingredient " << ingredientName << " not found in player's ingredient list." << std::endl;
    }
}
