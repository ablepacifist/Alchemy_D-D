#ifndef INVENTORY_H
#define INVENTORY_H

#include "Node.h"
#include "InventoryItem.h"
#include "IngredientList.h"
#include <iostream>
#include <fstream>

class Inventory {
public:
    Inventory();
    ~Inventory();

    void addItem(const InventoryItem &item);
    void display() const;
    InventoryItem* findItemByName(const std::string &name);
    void loadFromFile(const std::string &filename, const IngredientList &ingredientList);
    void saveToFile(const std::string &filename) const;
    void clear();
    Node <InventoryItem>* getHead() const;

    void increaseItemQuantity(const std::string &name, int amount);
    void decreaseItemQuantity(const std::string &name, int amount);
private:
    Node<InventoryItem>* head;

    void deleteList(Node<InventoryItem>* head);
};

#endif // INVENTORYLINKEDLIST_H

