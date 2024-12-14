#ifndef UI_H
#define UI_H

#include "Player.h"
#include "IngredientList.h"
#include "EffectList.h"
#include <string>

class UI {
public:
    UI();
    void start();

private:
    IngredientList masterList;
    EffectList effectList;
    Player* player;
    
    void initialize();
    void createPlayer();
    void displayMenu() const;
    void processCommand(const std::string& command);
    void displayInventory() const;
    void displayIngredientList() const;
    void combineIngredients();
    void displayHelp() const;
    void endProgram();
    void eat();
    void forage();
    void potion();
};

#endif // UI_H
