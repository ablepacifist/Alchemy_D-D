#ifndef INGREDIENTLIST_H
#define INGREDIENTLIST_H

#include "Node.h"
#include "EffectList.h"
#include <string>
#include <fstream>
#include <sstream>

class IngredientList {
private:
    Node<Ingredient>* head;

public:
    IngredientList() : head(nullptr) {}
    ~IngredientList();

    void addIngredient(const Ingredient& ingredient);
    void display() const;
    void loadFromFile(const std::string& filename, const EffectList& effectList); // Ensure this matches
    bool isFileEmpty(std::ifstream& file) const;
    //getters
    Node<Ingredient>* getHead() const;
    Ingredient* getByName(const std::string& name) const;
    Ingredient* getByIndex(int index);
    int getSize();
};

#endif

