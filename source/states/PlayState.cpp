#include "../core/GameManager.hpp"
#include "MainMenu/MainMenuState.hpp"
#include "PlayState.hpp"
#include <citro2d.h>

#include <assert.h>
#include <stdlib.h>

static C2D_SpriteSheet spriteSheet;
static C2D_Sprite sprite;

PlayState::PlayState(GameManager& game) : State(game) {}
PlayState::~PlayState() {
	C2D_SpriteSheetFree(spriteSheet);
};

bool PlayState::init() {
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/profile_fleur.t3x");
    if (!spriteSheet) return false;
	C2D_SpriteFromSheet(&sprite, spriteSheet, 0);

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
	C2D_DrawSprite(&sprite);

}

void PlayState::renderBott() {
	C2D_DrawSprite(&sprite);

}