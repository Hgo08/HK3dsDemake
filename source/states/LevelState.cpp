#include "../core/GameManager.hpp"
#include "c2d/base.h"
#include "LevelState.hpp"

LevelState::LevelState(GameManager& game) : State(game) {
    init();
}

bool LevelState::init() {
    return true;
}
void LevelState::handleInput() {

}

bool LevelState::update() {
    return true;
}
void LevelState::renderTop() {
    C2D_DrawRectSolid(10, 10, 1, 100, 100, C2D_Color32(035, 112, 234, 200));
}

void LevelState::renderBott() {

}