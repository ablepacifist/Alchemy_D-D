#include "IngredientList.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Destructor to free the allocated memory
IngredientList::~IngredientList()
{
    Node<Ingredient> *current = head;
    while (current != nullptr)
    {
        Node<Ingredient> *toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

// Add ingredient to the list
void IngredientList::addIngredient(const Ingredient &ingredient)
{
    Node<Ingredient> *newNode = new Node<Ingredient>(ingredient);
    newNode->next = head;
    head = newNode;
}

// Display all ingredients and their effects
void IngredientList::display() const
{
    Node<Ingredient> *current = head;
    while (current != nullptr)
    {
        current->data.display();
        current = current->next;
    }
}

// New function to check if a file is empty
bool IngredientList::isFileEmpty(std::ifstream &file) const
{
    return file.peek() == std::ifstream::traits_type::eof();
}

// Load ingredients and their effects from a file
void IngredientList::loadFromFile(const std::string &filename, const EffectList &effectList)
{
    std::ifstream file(filename);
    std::string line;
    std::cout << "Reading file: " << filename << std::endl;

    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    if (isFileEmpty(file))
    {
        std::cout << "File is empty." << std::endl;
        return;
    }

    int count = 0;
    while (std::getline(file, line))
    {
        count += 1;
        std::istringstream iss(line);
        std::string name, effect1, effect2, effect3, effect4;

        std::getline(iss, name, ',');
        std::getline(iss, effect1, ',');
        std::getline(iss, effect2, ',');
        std::getline(iss, effect3, ',');
        std::getline(iss, effect4, ',');

        try
        {
            std::array<Effect, 4> effects = {
                effectList.getEffectByName(effect1),
                effectList.getEffectByName(effect2),
                effectList.getEffectByName(effect3),
                effectList.getEffectByName(effect4)};

            Ingredient ingredient(count, name, effects);
            addIngredient(ingredient);

            // Debug statement to verify ingredient loading
            /*
            std::cout << "Loaded Ingredient: " << name << std::endl;
            for (const auto &effect : effects)
            {
                std::cout << "  Effect ID: " << effect.getID() << ", Name: " << effect.getName() << std::endl;
            }
            */
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Error: Effect not found for ingredient '" << name << "' - Skipping ingredient." << std::endl;
            continue;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Invalid argument while processing ingredient '" << name << "' - Skipping ingredient." << std::endl;
            continue;
        }
    }
    std::cout << "Finished reading file: " << filename << std::endl;
}

// getters
int IngredientList::getSize()
{
    Node<Ingredient> *current = head;
    int size = 0;
    while (current != nullptr)
    {
        current = current->next;
        size++;
    }
    return size;
}
Node<Ingredient> *IngredientList::getHead() const
{
    return head;
}
Ingredient *IngredientList::getByName(const std::string &name) const
{
    Node<Ingredient> *current = head;
    while (current != nullptr)
    {
        if (current->data.getName() == name)
        {
            return &current->data;
            // Return a pointer to the found ingredient
        }
        current = current->next;
    }
    return nullptr; // Return nullptr if the ingredient is not found
}
Ingredient *IngredientList::getByIndex(int index)
{
    Node<Ingredient> *current = head;
    int currentIndex = 0;
    while (current != nullptr)
    {
        if (currentIndex == index)
        {
            return &current->data;
        }
        current = current->next;
        currentIndex++;
    }
    throw std::out_of_range("Index out of range");
}
