#include "../core/GameManager.hpp"
#include "OptionsState.hpp"
#include "MainMenuState.hpp"

OptionsState::OptionsState(GameManager& game) : State(game) {}

bool OptionsState::init() {
    return true;
}
void OptionsState::handleInput() {

}

bool OptionsState::update() {
    
	u32 kDown = hidKeysDown();
	if (kDown & KEY_SELECT)
		return false; // break in order to return to hbmenu
    if (kDown & KEY_B)
        //game.changeState(std::make_unique<MainMenuState>(game));
        game.popState();


    return true;
}
void OptionsState::renderTop() {
    C2D_DrawRectSolid(10, 10, 1, 100, 100, C2D_Color32(035, 112, 234, 200));
}

void OptionsState::renderBott() {

}