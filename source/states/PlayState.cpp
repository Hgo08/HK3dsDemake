#include "../core/GameManager.hpp"
#include "MainMenu/MainMenuState.hpp"
#include "PlayState.hpp"
#include <citro2d.h>
#include "MainMenu/UI/SavesMenu.hpp"
#include "MainMenu/MainMenuState.hpp"
#include "../core/KeybindsManager.hpp"

#include <assert.h>
#include <memory>
#include <stdlib.h>
#include <utility>

PlayState::PlayState(GameManager& game) : State(game) {}
PlayState::~PlayState() {};

int x = 10;
int y = 10;

bool PlayState::init() {
    return true;
}

bool PlayState::update() {
    
	u32 kDown = hidKeysDown();

    KeybindsManager& input = KeybindsManager::getInstance();

    if (input.isActionHeld(Action::Right)) {
        x += 3;
    }
    if (input.isActionHeld(Action::Left)){
        x -= 3;
    }
    if (input.isActionHeld(Action::Up)){
        y -= 3;
    }
    if (input.isActionHeld(Action::Down)){
        y += 3;
    }

    if (kDown & KEY_B){
		std::unique_ptr<MainMenuState> state = std::make_unique<MainMenuState>(game);
		//idk if i could make it go to the "SavesMenu" instead of the "ManiMenuView" menu
        game.changeState(std::move(state));
	}


    return true;
}
void PlayState::renderTop() {
    C2D_DrawRectSolid(x, y, 1, 100, 100, C2D_Color32(235, 112, 134, 200));

}

void PlayState::renderBott() {

}