#include "EffectList.h"
#include <iostream>

// Destructor
EffectList::~EffectList() {
    Node<Effect>* current = head;
    while (current != nullptr) {
        Node<Effect>* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

// Add effect to the list
void EffectList::addEffect(const Effect& effect) {
    Node<Effect>* newNode = new Node<Effect>(effect);
    newNode->next = head;
    head = newNode;
    //std::cout << "Added: " << effect.getName() << std::endl;
}

// Display all effects
void EffectList::display() const {
    Node<Effect>* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

// Check if file is empty
bool EffectList::isFileEmpty(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

// Load effects from file
void EffectList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::cout << "Reading file: " << filename << std::endl;
    
    // Check if the file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    if (isFileEmpty(file)) {
        std::cout << "File is empty." << std::endl;
        return;
    }
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string idStr, name;
        std::getline(iss, idStr, ',');
        std::getline(iss, name, ',');

        int id = std::stoi(idStr);
        Effect effect(id, name);
        
        addEffect(effect);
    }
    std::cout << "Finished reading file: " << filename << std::endl;
}

// Get effect by ID
Effect EffectList::getEffectById(int id) const {
    Node<Effect>* current = head;
    while (current != nullptr) {
        if (current->data.getID() == id) {
            return current->data;
        }
        current = current->next;
    }
    throw std::out_of_range("Effect ID not found");
}

// Get effect by name
Effect EffectList::getEffectByName(const std::string& name) const {
    Node<Effect>* current = head;
    while (current != nullptr) {
        if (current->data.getName() == name) {
            return current->data;
        }
        current = current->next;
    }
    std::cout << "cant find effect"<<std::endl;
    throw std::out_of_range("Effect name not found");
}
int EffectList::getSize(){
    Node<Effect>* current = head;
    int size =0;
    while (current != nullptr) {
        current = current->next;
        size++;
    }
    return size;
}
