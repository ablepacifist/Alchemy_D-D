#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "IngredientList.h"

Inventory::Inventory() : head(nullptr) {}

Inventory::~Inventory()
{
    clear();
}

void Inventory::addItem(const InventoryItem &item)
{
    std::cout << "in addItem" << std::endl;
    Node<InventoryItem> *current = head;

    // See if we already have that in the list:
    while (current != nullptr)
    {
        std::cout << "looking at: " << current->data.getName() << std::endl;
        if (current->data.getName() == item.getName())
        {
            // Check if it's an ingredient or potion and handle accordingly
            if (current->data.isIngredient() && item.isIngredient())
            {
                current->data.updateQuantity(current->data.getQuantity() + item.getQuantity());
            }
            else if (current->data.isPotion() && item.isPotion())
            {
                // Potions with the same name and effects should be merged
                // but if we want unique potions, just add a new one instead
                // of updating the quantity.
                current->data.updateQuantity(current->data.getQuantity() + item.getQuantity());
            }
            std::cout << "found existing item: " << current->data.getName() << std::endl;
            std::cout << "new quantity: " << current->data.getQuantity() << std::endl;
            return;
        }
        current = current->next;
    }

    std::cout << "item not in list yet" << std::endl;
    // Add new item to the list
    Node<InventoryItem> *newItem = new Node<InventoryItem>(item);
    newItem->next = head;
    head = newItem;
}

void Inventory::display() const
{
    Node<InventoryItem> *current = head;
    while (current != nullptr)
    {
        current->data.display();
        std::cout << "Quantity: " << current->data.getQuantity() << std::endl;
        current = current->next;
    }
}

Node<InventoryItem> *Inventory::getHead() const
{
    return head;
}

InventoryItem *Inventory::findItemByName(const std::string &name)
{
    Node<InventoryItem> *current = head;
    while (current != nullptr)
    {
        if (current->data.getName() == name)
        {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

// file managment
#include "Inventory.h"
#include <sstream>

void Inventory::loadFromFile(const std::string &filename, const IngredientList &ingredientList)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type, name, effect1, effect2, effect3, effect4;
        int quantity;

        std::getline(iss, type, ',');
        if (type == "Ingredient")
        {
            std::getline(iss, name, ',');
            iss >> quantity;
            Ingredient *ingredient = ingredientList.getByName(name);
            if (ingredient)
            {
                InventoryItem item(*ingredient, quantity);
                addItem(item);
            }
        }
        else if (type == "Potion")
        {
            std::getline(iss, effect1, ',');
            std::getline(iss, effect2, ',');
            std::getline(iss, effect3, ',');
            std::getline(iss, effect4, ',');
            iss >> quantity;
            std::array<Effect, 4> effects = {
                Effect(1, effect1), // Assuming Effect constructor accepts ID and name
                Effect(2, effect2),
                Effect(3, effect3),
                Effect(4, effect4)};
            std::string potionName = "Potion of ";
            for (size_t i = 0; i < 4; ++i)
            {
                if (!(effects[i].getName() == "NULL"))
                {
                    if (i > 0)
                    {
                        potionName += " and ";
                    }
                    potionName += effects[i].getName();
                }
            }
            Potion potion(potionName, effects); 
            InventoryItem item(potion, quantity);    
            addItem(item);
        }
    }

    file.close();
}

void Inventory::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    Node<InventoryItem> *current = head;
    while (current != nullptr)
    {
        if (current->data.isIngredient())
        {
            file << "Ingredient," << current->data.getName() << "," << current->data.getQuantity() << std::endl;
        }
        else if (current->data.isPotion())
        {
            std::array<Effect, 4> effects = current->data.getPotion().getEffects();
            file << "Potion";
            for (const auto &effect : effects)
            {
                file << "," << effect.getName();
            }
            file << "," << current->data.getQuantity() << std::endl;
        }
        current = current->next;
    }

    file.close();
}

// change quantity:
void Inventory::increaseItemQuantity(const std::string &name, int amount)
{
    InventoryItem *item = findItemByName(name);
    if (item)
    {
        item->updateQuantity(item->getQuantity() + amount);
    }
    else
    {
        std::cerr << "Item " << name << " not found in inventory." << std::endl;
    }
}
void Inventory::decreaseItemQuantity(const std::string &name, int amount)
{
    InventoryItem *item = findItemByName(name);
    if (item)
    {
        int newQuantity = item->getQuantity() - amount;
        if (newQuantity >= 0)
        {
            item->updateQuantity(newQuantity);
        }
        else
        {
            std::cerr << "Cannot decrease " << name << " quantity below 0." << std::endl;
        }
    }
    else
    {
        std::cerr << "item " << name << " not found in inventory." << std::endl;
    }
}

// delete:
void Inventory::clear()
{
    deleteList(head);
    head = nullptr;
}
void Inventory::deleteList(Node<InventoryItem> *head)
{
    while (head != nullptr)
    {
        Node<InventoryItem> *temp = head;
        head = head->next;
        delete temp;
    }
}