#include "../core/GameManager.hpp"
#include "MainMenu/MainMenuState.hpp"
#include "PlayState.hpp"
#include <citro2d.h>
#include "MainMenu/UI/SavesMenu.hpp"
#include "MainMenu/MainMenuState.hpp"


#include <assert.h>
#include <memory>
#include <stdlib.h>
#include <utility>

PlayState::PlayState(GameManager& game) : State(game) {}
PlayState::~PlayState() {};

bool PlayState::init() {
    return true;
}

bool PlayState::update() {
    
	u32 kDown = hidKeysDown();

    if (kDown & KEY_B){
		std::unique_ptr<MainMenuState> state = std::make_unique<MainMenuState>(game);
		//idk if i could make it go to the saveMenu instead of the "ManiMenuView" menu
        game.changeState(std::move(state));
	}


    return true;
}
void PlayState::renderTop() {
    C2D_DrawRectSolid(10, 10, 1, 100, 100, C2D_Color32(235, 112, 134, 200));

}

void PlayState::renderBott() {

}