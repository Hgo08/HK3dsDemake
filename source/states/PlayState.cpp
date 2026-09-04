#include "../core/GameManager.hpp"
#include "MainMenu/MainMenuState.hpp"
#include "PlayState.hpp"

PlayState::PlayState(GameManager& game) : State(game) {}

bool PlayState::init() {
    return true;
}
void PlayState::handleInput() {

}

bool PlayState::update() {
    
	u32 kDown = hidKeysDown();
	if (kDown & KEY_SELECT)
		return false; // break in order to return to hbmenu
    if (kDown & KEY_B)
        game.changeState(std::make_unique<MainMenuState>(game));

    return true;
}
void PlayState::renderTop() {
    C2D_DrawRectSolid(10, 10, 1, 100, 100, C2D_Color32(235, 112, 134, 200));
}

void PlayState::renderBott() {

}