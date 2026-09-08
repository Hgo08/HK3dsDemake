#include "../MainMenuState.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include "3ds/services/hid.h"
#include "OptionsMenu.hpp"
#include "ControlsMenu.hpp"
#include <memory>

ControlsMenu::ControlsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

ControlsMenu::~ControlsMenu() {
    if (textBuff) {
        C2D_TextBufDelete(textBuff);
    }
    if (buttons_sprites_sheet) {
        C2D_SpriteSheetFree(buttons_sprites_sheet);
    }
}

Action ControlsMenu::getActionForButtonIndex(int index) const {
    switch (index) {
        case 0:  return Action::Up;
        case 1:  return Action::Left;
        case 2:  return Action::Down;
        case 3:  return Action::Right;
        case 4:  return Action::Jump;
        case 5:  return Action::QuickMap;
        case 6:  return Action::Attack;
        case 7:  return Action::SuperDash;
        case 8:  return Action::Dash;
        case 9:  return Action::DreamNail;
        case 10: return Action::Focus;
        case 11: return Action::QuickCast;
        case 12: return Action::Inventory;
        default: return Action::Count;
    }
}

int ControlsMenu::getSpriteIndexForKey(u32 key) const {
    if (key & KEY_A)                         return 0;  // button_A.png
    if (key & KEY_B)                         return 1;  // button_B.png
    if (key & KEY_X)                         return 2;  // button_X.png
    if (key & KEY_Y)                         return 3;  // button_Y.png
    if (key & KEY_L)                         return 4;  // button_L.png
    if (key & KEY_R)                         return 5;  // button_R.png
    if (key & KEY_ZL)                        return 6;  // button_ZL.png
    if (key & KEY_ZR)                        return 7;  // button_ZR.png
    if (key & (KEY_DLEFT | KEY_CPAD_LEFT))   return 8;  // button_left.png
    if (key & (KEY_DRIGHT | KEY_CPAD_RIGHT)) return 9;  // button_right.png
    if (key & (KEY_DUP | KEY_CPAD_UP))       return 10; // button_up.png
    if (key & (KEY_DDOWN | KEY_CPAD_DOWN))   return 11; // button_down.png

    return -1;
}

bool ControlsMenu::init() {

    textBuff = C2D_TextBufNew(128);

    buttons_sprites_sheet = C2D_SpriteSheetLoad("romfs:/gfx/buttons.t3x");
    if (buttons_sprites_sheet) {
        for (int i = 0; i < 12; i++) {
            images[i] = C2D_SpriteSheetGetImage(buttons_sprites_sheet, i);
        }
    }



    for (int i = 0; i < 6; i++) {
        int leftIndex = i * 2;
        Action leftAction = getActionForButtonIndex(leftIndex);
        auto buttonsLeft = std::make_unique<Button>();
        buttonsLeft->init(20, i*22+50, 120, 20, [leftAction](){
            KeybindsManager::getInstance().startListening(leftAction);
        });
        buttons.push_back(std::move(buttonsLeft));

        int rightIndex = i * 2 + 1;
        Action rightAction = getActionForButtonIndex(rightIndex);
        auto buttonsRight = std::make_unique<Button>();
        buttonsRight->init(180, i*22+50, 120, 20, [rightAction](){
            KeybindsManager::getInstance().startListening(rightAction);
        });
        buttons.push_back(std::move(buttonsRight));
    }
    
    // Inventory button (Row 6)
    Action inventoryAction = getActionForButtonIndex(12);
    auto buttonsLeft = std::make_unique<Button>();
    buttonsLeft->init(100, 6*22+50, 120, 20, [inventoryAction](){
        KeybindsManager::getInstance().startListening(inventoryAction);
    });
    buttons.push_back(std::move(buttonsLeft));

    C2D_TextFontParse(&texts[0], state.font, textBuff, "Up");
    C2D_TextFontParse(&texts[1], state.font, textBuff, "Down");
    C2D_TextFontParse(&texts[2], state.font, textBuff, "Jump");
    C2D_TextFontParse(&texts[3], state.font, textBuff, "Attack");
    C2D_TextFontParse(&texts[4], state.font, textBuff, "Dash");
    C2D_TextFontParse(&texts[5], state.font, textBuff, "Focus/Cast");

    C2D_TextFontParse(&texts[6], state.font, textBuff, "Left");
    C2D_TextFontParse(&texts[7], state.font, textBuff, "Right");
    C2D_TextFontParse(&texts[8], state.font, textBuff, "Quick map");
    C2D_TextFontParse(&texts[9], state.font, textBuff, "Super dash");
    C2D_TextFontParse(&texts[10], state.font, textBuff, "Dream nail");
    C2D_TextFontParse(&texts[11], state.font, textBuff, "Quick cast");

    C2D_TextFontParse(&texts[12], state.font, textBuff, "Inventory");
    
    C2D_TextFontParse(&listeningText, state.font, textBuff, "Press...");
    C2D_TextFontParse(&selectButtonText, state.font, textBuff, "SELECT");
    C2D_TextFontParse(&startButtonText, state.font, textBuff, "START");
    
    for (int i = 0; i < 13; i++) {
        C2D_TextOptimize(&texts[i]);
    }
    C2D_TextOptimize(&listeningText);
    C2D_TextOptimize(&selectButtonText);
    C2D_TextOptimize(&startButtonText);

    auto btnBack = std::make_unique<TextButton>();
    btnBack->init(state.font, textBuff, "Back", -1, 215, 0.65, 10, 10, [this]() {
        back();
    });
    buttons.push_back(std::move(btnBack));

    return true;
}

void ControlsMenu::update() {
    KeybindsManager& input = KeybindsManager::getInstance();
    if (input.getIsListening()) {
        input.update();
        return;
    }
    menuNavegation();
}

void ControlsMenu::renderTop() {

}

void ControlsMenu::renderBott() {
    // render UI Buttons and selection outlines
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);
        buttons[i]->render(isSelected);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3, 0.6f);
        }
    }

    // render Left and Right grid columns
    for (int i = 0; i < 6; i++) {
        float yPos = i * 22 + 52.5f;

        // Left Column (Grid Index: i * 2)
        Action leftAction = getActionForButtonIndex(i * 2);
        renderActionButton(leftAction, 20.0f, 120.0f, yPos, i);

        // Right Column (Grid Index: i * 2 + 1)
        Action rightAction = getActionForButtonIndex(i * 2 + 1);
        renderActionButton(rightAction, 180.0f, 280.0f, yPos, i + 6);
    }

    // render Inventory Row (Row 6, Index 12)
    Action inventoryAction = getActionForButtonIndex(12);
    renderActionButton(inventoryAction, 100.0f, 200.0f, 6 * 22 + 52.0f, 12);
}

void ControlsMenu::back() {
    menuManager.changeMenu(std::make_unique<OptionsMenu>(state, menuManager));
}

void ControlsMenu::menuNavegation() {
    if (buttons.empty()) return;

    u32 kDown = hidKeysDown();

    // Handle touch input
    if (kDown & KEY_TOUCH) {
        touchPosition touch;
        hidTouchRead(&touch);

        for (size_t i = 0; i < buttons.size(); i++) {
            if (buttons[i]->handleTouch(kDown, touch)) {
                selectedButtonIndex = static_cast<int>(i);
                break;
            }
        }
    }

    const int totalGridButtons = 12; // 6 rows * 2 columns
    const int inventoryIndex = 12;
    const int backButtonIndex = 13;

    // Navigate Right
    if (kDown & (KEY_RIGHT | KEY_DRIGHT | KEY_CSTICK_RIGHT)) {
        // Move from Left column (even index) to Right column (odd index)
        if (selectedButtonIndex < totalGridButtons && selectedButtonIndex % 2 == 0) {
            selectedButtonIndex += 1;
        }
    }
    // Navigate Left
    else if (kDown & (KEY_LEFT | KEY_DLEFT | KEY_CSTICK_LEFT)) {
        // Move from Right column (odd index) to Left column (even index)
        if (selectedButtonIndex < totalGridButtons && selectedButtonIndex % 2 != 0) {
            selectedButtonIndex -= 1;
        }
    }
    // Navigate Down
    else if (kDown & (KEY_DOWN | KEY_DDOWN | KEY_CSTICK_DOWN)) {
        if (selectedButtonIndex < totalGridButtons - 2) {
            // Move down one row
            selectedButtonIndex += 2;
        }
        else if (selectedButtonIndex == 10 || selectedButtonIndex == 11) {
            // From bottom row of grid to Inventory
            selectedButtonIndex = inventoryIndex;
        }
        else if (selectedButtonIndex == inventoryIndex) {
            selectedButtonIndex = backButtonIndex;
        }
        else if (selectedButtonIndex == backButtonIndex) {
            selectedButtonIndex = 0;
        }
    }
    // Navigate Up
    else if (kDown & (KEY_UP | KEY_DUP | KEY_CSTICK_UP)) {
        if (selectedButtonIndex == 0 || selectedButtonIndex == 1) {
            // Wrap around to Back button
            selectedButtonIndex = backButtonIndex;
        }
        else if (selectedButtonIndex > 1 && selectedButtonIndex < totalGridButtons) {
            // Move up one row
            selectedButtonIndex -= 2;
        }
        else if (selectedButtonIndex == inventoryIndex) {
            // Return to bottom-left element of the grid
            selectedButtonIndex = 10;
        }
        else if (selectedButtonIndex == backButtonIndex) {
            selectedButtonIndex = inventoryIndex;
        }
    }

    // Trigger action
    if (kDown & KEY_A) {
        buttons[selectedButtonIndex]->click();
    }
}

void ControlsMenu::renderActionButton(Action action, float labelX, float spriteX, float yPos, int labelTextIndex) {
    KeybindsManager& input = KeybindsManager::getInstance();

    // Render Action Label Text
    C2D_DrawText(&texts[labelTextIndex], C2D_WithColor, labelX, yPos, 0.5f, 0.55f, 0.55f, C2D_Color32(255, 255, 255, 255));

    // If currently listening for this action, render waiting prompt
    if (input.getIsListening() && input.getActionBeingRebound() == action) {
        C2D_DrawText(&listeningText, C2D_WithColor, spriteX - 10, yPos, 0.5f, 0.45f, 0.45f, C2D_Color32(255, 255, 0, 255));
        return;
    }

    // Render bound key sprite icon
    u32 boundKey = input.getBoundKey(action);
    int spriteIndex = getSpriteIndexForKey(boundKey);

    if (boundKey & KEY_SELECT) {
        C2D_DrawText(&selectButtonText, C2D_WithColor, spriteX - 10, yPos, 0.5f, 0.45f, 0.45f, C2D_Color32(255, 255, 255, 255));
    }
    if (boundKey & KEY_START) {
        C2D_DrawText(&startButtonText, C2D_WithColor, spriteX - 10, yPos, 0.5f, 0.45f, 0.45f, C2D_Color32(255, 255, 255, 255));
    }

    if (spriteIndex >= 0 && spriteIndex < 12 && buttons_sprites_sheet) {
        C2D_DrawImageAt(images[spriteIndex], spriteX, yPos, 0.5f, NULL, 0.5f, 0.5f);
    }
}