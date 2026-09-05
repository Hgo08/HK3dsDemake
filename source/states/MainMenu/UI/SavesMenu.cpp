#include "../../../core/MenuManager.hpp"
#include "MainMenuView.hpp"
#include "SavesMenu.hpp"

SavesMenu::SavesMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool SavesMenu::init(){
    
    return true;
}
void SavesMenu::update(){

}
void SavesMenu::renderTop(){

}
void SavesMenu::renderBott(){

}
void SavesMenu::back(){
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}