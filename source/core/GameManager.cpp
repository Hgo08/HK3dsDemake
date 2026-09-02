#include <3ds.h>
#include "GameManager.hpp"
#include "State.hpp"
#include "../states/MainMenuState.hpp"

using namespace std;

GameManager::GameManager(){}

bool GameManager::init(){
    romfsInit();
	cfguInit(); // only to allow C2D_FontLoadSystem to work
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	top  = C2D_CreateScreenTarget(GFX_TOP,    GFX_LEFT);
	bott = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);


    pushState(make_unique<MainMenuState>(*this));

    return true;
}
bool GameManager::update(){
    //Backup exit way if there is no state -----------------------
    if (states.empty()){
        hidScanInput();

	    // Respond to user input
	    u32 kDown = hidKeysDown();
	    if (kDown & KEY_START)
	    	return false; // break in order to return to hbmenu
    }

    //-------------------------------------------------------------
    
    //for (const auto &state : states) {
    //    state->update();
    //}
    return states.back()->update();

    return true;
}
bool GameManager::render(){
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

	C2D_TargetClear(top,  C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
	C2D_SceneBegin(top);
	//render TOP

    // because its a unique pointer, we need to put the & so state is a reference of the member in the list
    // without & state would be a new variable coping the one in states and we dont want multiplied states
    for (const auto &state : states) {
        state->renderTop();
    }

    C2D_TargetClear(bott, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
	C2D_SceneBegin(bott);
    //render BOTT
    //state.renderBot

    // because its a unique pointer, we need to put the & so state is a reference of the member in the list
    // without & state would be a new variable coping the one in states and we dont want multiplied states
    for (const auto &state : states) {
        state->renderBott();
    }

	C3D_FrameEnd(0);
    return true;
}
void GameManager::exit(){

    //clearing the list (vector) deletes all states objects so it calls the destructor and delete de variables/exit the libraries
    states.clear();

    C2D_Fini();
	C3D_Fini();
	gfxExit();
	cfguExit();
	romfsExit();
}

// states functions
void GameManager::pushState(unique_ptr<State> state) {
    states.push_back(std::move(state));
}
void GameManager::popState() {
    states.pop_back();
}
