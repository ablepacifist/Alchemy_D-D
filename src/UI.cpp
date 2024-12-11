#include "UI.h"
#include <iostream>
#include <sstream>
#include <filesystem>

UI::UI() : player(nullptr) {}

void UI::start()
{
    initialize();
    createPlayer();
    std::string command;
    while (true)
    {
        std::cout << "\nEnter command (h for help): ";
        std::getline(std::cin, command);
        if (command == "exit")
        {
            endProgram();
            break;
        }
        processCommand(command);
    }
}

void UI::initialize()
{
    // Initialize master list and effect list
    fs::path exePath = fs::current_path();   // Gets the current working directory
    fs::path dataPath = exePath / "../data"; // Go up one level to the root and then into the data folder
    fs::path effectsFilePath = fs::absolute(dataPath / "effects.txt");
    effectList.loadFromFile(effectsFilePath.string());

    fs::path masterListFilePath = fs::absolute(dataPath / "masterList.txt");
    masterList.loadFromFile(masterListFilePath.string(), effectList);

    std::cout << "Master ingredient list and effects loaded." << std::endl;
}

void UI::createPlayer()
{
    std::string playerName;
    std::cout << "Enter player name(capitalized): ";
    std::getline(std::cin, playerName);
    player = new Player(1, playerName, masterList);
    std::cout << "Player " << playerName << " created." << std::endl;
}

void UI::displayMenu() const
{
    std::cout << "\nCommands:\n"
              << "inv - Display inventory\n"
              << "tome - Display player ingredient list\n"
              << "craft/combine - Combine ingredients\n"
              << "h - Display this help message\n"
              << "eat - consume one ingredient and learn its effects\n"
              << "exit - Exit the program\n";
}

void UI::processCommand(const std::string &command)
{
    if (command == "inv")
    {
        displayInventory();
    }
    else if (command == "tome")
    {
        displayIngredientList();
    }
    else if (command == "craft" || command == "combine")
    {
        combineIngredients();
    }
    else if (command == "h")
    {
        displayHelp();
    }
    else if(command == "eat"){
        eat();
    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
        displayHelp();
    }
}

void UI::displayInventory() const
{
    player->displayInventory();
}

void UI::displayIngredientList() const
{
    player->displayIngredients();
}

void UI::combineIngredients()
{
    std::string input;
    std::cout << "Enter two ingredient names separated by a comma: ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::string ingredient1Name, ingredient2Name;

    if (std::getline(iss, ingredient1Name, ',') && std::getline(iss, ingredient2Name))
    {
        player->combineIngredients(ingredient1Name, ingredient2Name);
    }
    else
    {
        std::cerr << "Invalid input. Please enter two ingredient names separated by a comma." << std::endl;
    }
}
void UI::eat(){
    std::string input;
    std::cout << "Enter ingredient name: ";
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::string ingredientName;

    if (std::getline(iss, ingredientName) )
    {
        player->eat(ingredientName);
    }
    else
    {
        std::cerr << "Invalid input. Please enter two ingredient names separated by a comma." << std::endl;
    } 
}
void UI::displayHelp() const
{
    displayMenu();
}
void UI::endProgram()
{
    std::cout << "Save ingredient list..." << std::endl;
    player->saveIngredientList();
    std::cout << "Save ingredient list completed" << std::endl;
    std::cout << "Save inventory..." << std::endl;
    player->saveInventory();
    std::cout << "Save inventory completed" << std::endl;

    std::cout << "Program finished successfully" << std::endl;
}
