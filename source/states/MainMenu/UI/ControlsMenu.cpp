#include "../MainMenuState.hpp"
#include "../../../core/UI/MenuManager.hpp"
#include "OptionsMenu.hpp"
#include "ControlsMenu.hpp"
#include <memory>

ControlsMenu::ControlsMenu(MainMenuState& state, MenuManager& menuManager)
    : state(state), menuManager(menuManager) {}

bool ControlsMenu::init() {

    textBuff = C2D_TextBufNew(128);

    buttons_sprites_sheet = C2D_SpriteSheetLoad("romfs:/gfx/buttons.t3x");
    for (int i = 0; i < 12; i++) {
        images[i] = C2D_SpriteSheetGetImage(buttons_sprites_sheet, i);
    }


    for (int i = 0; i < 6; i++) {
        auto buttonsLeft = std::make_unique<Button>();
        buttonsLeft->init(20, i*22+50, 120, 20);
        buttons.push_back(std::move(buttonsLeft));

        auto buttonsRight = std::make_unique<Button>();
        buttonsRight->init(180, i*22+50, 120, 20);
        buttons.push_back(std::move(buttonsRight));
    }

    auto buttonsLeft = std::make_unique<Button>();
    buttonsLeft->init(100, 6*22+50, 120, 20);
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

    for (int i = 0; i < 13; i++) {
        C2D_TextOptimize(&texts[i]);
    }

    auto btnBack = std::make_unique<TextButton>();
    btnBack->init(state.font, textBuff, "Back", -1, 215, 0.65, 10, 10, [this]() {
        back();
    });
    buttons.push_back(std::move(btnBack));

    return true;
}

void ControlsMenu::update() {
    menuNavegation();
}

void ControlsMenu::renderTop() {

}

void ControlsMenu::renderBott() {
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isSelected = (static_cast<int>(i) == selectedButtonIndex);

        buttons[i]->render(isSelected);

        if (isSelected) {
            drawSelectionDecorators(*buttons[i], state.selected_text_decorator, 3, 0.6);
        }
    }
    for (int i = 0; i < 6; i++) {
        C2D_DrawText(&texts[i], C2D_WithColor, 20, i*22+52.5,  0.5f, 0.6, 0.6, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&texts[i+6], C2D_WithColor, 180, i*22+52.5,  0.5f, 0.6, 0.6, C2D_Color32(255, 255, 255, 255));
        C2D_DrawImageAt(images[i], 120, i*22+52.5, 0, NULL, 0.5, 0.5);
        C2D_DrawImageAt(images[i+6], 280, i*22+52.5, 0, NULL, 0.5, 0.5);
    }
    C2D_DrawText(&texts[12], C2D_WithColor, 100, 6*22+52,  0.5f, 0.55, 0.55, C2D_Color32(255, 255, 255, 255));
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