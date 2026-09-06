#include "../../../core/UI/MenuManager.hpp"
#include "../../../core/GameManager.hpp"
#include "../../PlayState.hpp"
#include "3ds/services/hid.h"
#include "MainMenuView.hpp"
#include "SavesMenu.hpp"
#include "../MainMenuState.hpp"
#include "c2d/spritesheet.h"
#include <cstddef>
#include <string>

SavesMenu::SavesMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool SavesMenu::init(){
    //imgs
    profileFleurSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/profile_fleur.t3x"); 
    areaArtSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/area_art_godshome.t3x"); 
    if (!profileFleurSpriteSheet || !areaArtSpriteSheet) return false;
    profileFleurImg = C2D_SpriteSheetGetImage(profileFleurSpriteSheet,0); //211 x 22
    godhomeAreaImg = C2D_SpriteSheetGetImage(areaArtSpriteSheet, 0); //183 x 29
    
    //text
    staticBuff = C2D_TextBufNew(16);

    //save numbers and buttons
    for (int i = 0; i < 4; i++) {
        C2D_TextFontParse(&saveNumberObj[i], state.font, staticBuff, (std::to_string(i+1) + ".").c_str());
        C2D_TextOptimize(&saveNumberObj[i]);
        auto saveBttn= std::make_unique<Button>();
        saveBttn->init(20, i*38+60, 210, 30, [this](){state.getGame().changeState(std::make_unique<PlayState>(state.getGame()));;});
        buttons.push_back(std::move(saveBttn));
    }
 
    //back btn
    auto btnBack = std::make_unique<TextButton>();
    btnBack->init(state.font, staticBuff, "Back", -1, 215, 0.65, 10, 10, [this]() {
        back();
    });
    buttons.push_back(std::move(btnBack));
    return true;
}
void SavesMenu::update(){
    UIMenu::update();
}
void SavesMenu::renderTop(){

}
void SavesMenu::renderBott(){
    for (int i = 0; i < 4; i++) {
        C2D_DrawImageAt(profileFleurImg, 20,  i*38+60, 0.5, nullptr, 1, 1);
        C2D_DrawImageAt(godhomeAreaImg, 33,  i*38+62, 0.5, nullptr, 1, 1);
        C2D_DrawText(&saveNumberObj[i], C2D_WithColor, 33, i*38+70,   0.5f, 0.6, 0.6, C2D_Color32(255, 255, 255, 255));
    }
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);

        buttons[i]->render(isSelected);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3, 0.6);
        }
    }
}
void SavesMenu::back(){
    menuManager.changeMenu(std::make_unique<MainMenuView>(state, menuManager));
}