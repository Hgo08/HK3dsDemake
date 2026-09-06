#pragma once
#include <string>
#include <vector>
#include <memory>
#include <3ds.h>
#include <citro2d.h>
#include "3ds/services/hid.h"
#include "Button.hpp"

class UIMenu {
protected:
    std::vector<std::unique_ptr<Button>> buttons;
    int selectedButtonIndex = 0;
public:
    virtual ~UIMenu() = default;
    virtual bool haveBackButton() const { return true; };

    virtual std::string getTitle() const { return ""; };

    virtual bool init() = 0;
    virtual void update(){
        if (buttons.empty()) return;
        
        u32 kDown = hidKeysDown();

        if (kDown & KEY_TOUCH) {
            touchPosition touch;
            hidTouchRead(&touch);

            for (int i = 0; i < buttons.size(); i++) {
                if (buttons[i]->handleTouch(kDown, touch)) {
                    selectedButtonIndex = i;
                    break;
                }
            }
        }

        // use stick and arrows to go up and down on seleccted index
        if (kDown & (KEY_DOWN | KEY_DDOWN | KEY_CSTICK_DOWN)) {
            selectedButtonIndex = (selectedButtonIndex + 1) % buttons.size();
        } 
        else if (kDown & (KEY_UP | KEY_DUP | KEY_CSTICK_UP)) {
            selectedButtonIndex = (selectedButtonIndex - 1 + buttons.size()) % buttons.size();
        }

        // click seleccted button with "A"
        if (kDown & KEY_A) {
            buttons[selectedButtonIndex]->click();
        }
    };
    virtual void renderTop() = 0;
    virtual void renderBott() = 0;
    virtual void back() = 0;
};