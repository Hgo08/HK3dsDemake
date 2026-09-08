#include "KeybindsManager.hpp"
#include "3ds/services/hid.h"
#include <filesystem>
#include <fstream>

KeybindsManager::KeybindsManager() {
    setDefaults();
    loadFromFile(SAVE_PATH);
}

KeybindsManager& KeybindsManager::getInstance() {
    static KeybindsManager instance;
    return instance;
}

void KeybindsManager::setDefaults() {
    bindings[Action::Up]        = KEY_DUP | KEY_CPAD_UP;
    bindings[Action::Down]      = KEY_DDOWN | KEY_CPAD_DOWN;
    bindings[Action::Left]      = KEY_DLEFT | KEY_CPAD_LEFT;
    bindings[Action::Right]     = KEY_DRIGHT | KEY_CPAD_RIGHT;
    bindings[Action::Jump]      = KEY_B;
    bindings[Action::QuickMap]  = KEY_SELECT;
    bindings[Action::Attack]    = KEY_R;
    bindings[Action::SuperDash] = KEY_X;
    bindings[Action::Dash]      = KEY_L;
    bindings[Action::DreamNail] = KEY_A;
    bindings[Action::Focus]     = KEY_Y;
    //bindings[Action::QuickCast] = 
    bindings[Action::Inventory] = KEY_START;
}

u32 KeybindsManager::normalizeKey(u32 key) const {
    if (key & (KEY_DUP | KEY_CPAD_UP)) {
        key |= (KEY_DUP | KEY_CPAD_UP);
    }
    if (key & (KEY_DDOWN | KEY_CPAD_DOWN)) {
        key |= (KEY_DDOWN | KEY_CPAD_DOWN);
    }
    if (key & (KEY_DLEFT | KEY_CPAD_LEFT)) {
        key |= (KEY_DLEFT | KEY_CPAD_LEFT);
    }
    if (key & (KEY_DRIGHT | KEY_CPAD_RIGHT)) {
        key |= (KEY_DRIGHT | KEY_CPAD_RIGHT);
    }
    return key;
}

void KeybindsManager::startListening(Action action) {
    isListening = true;
    actionBeingRebound = action;
}

void KeybindsManager::update() {
    if (!isListening) return;

    u32 kDown = hidKeysDown();

    // Do nothing if no key was pressed in this frame
    if (kDown == 0) return;

    // Assign the new key, stop listening, and save to SD card
    bindings[actionBeingRebound] = normalizeKey(kDown);
    isListening = false;
    saveToFile(SAVE_PATH);
}

bool KeybindsManager::getIsListening() const {
    return isListening;
}

Action KeybindsManager::getActionBeingRebound() const {
    return actionBeingRebound;
}

bool KeybindsManager::isActionPressed(Action action) const {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        return (hidKeysDown() & it->second) != 0;
    }
    return false;
}

bool KeybindsManager::isActionHeld(Action action) const {
    auto it = bindings.find(action);
    if (it != bindings.end()) {
        return (hidKeysHeld() & it->second) != 0;
    }
    return false;
}

u32 KeybindsManager::getBoundKey(Action action) const {
    auto it = bindings.find(action);
    return (it != bindings.end()) ? it->second : 0;
}

std::string KeybindsManager::getKeyName(Action action) const {
    u32 key = getBoundKey(action);

    if (key & KEY_A) return "A";
    if (key & KEY_B) return "B";
    if (key & KEY_X) return "X";
    if (key & KEY_Y) return "Y";
    if (key & KEY_L) return "L";
    if (key & KEY_R) return "R";
    if (key & KEY_ZL) return "ZL";
    if (key & KEY_ZR) return "ZR";
    if (key & KEY_DUP) return "D-Pad Up";
    if (key & KEY_DDOWN) return "D-Pad Down";
    if (key & KEY_DLEFT) return "D-Pad Left";
    if (key & KEY_DRIGHT) return "D-Pad Right";
    if (key & KEY_CPAD_UP) return "Circle Pad Up";
    if (key & KEY_CPAD_DOWN) return "Circle Pad Down";
    if (key & KEY_CPAD_LEFT) return "Circle Pad Left";
    if (key & KEY_CPAD_RIGHT) return "Circle Pad Right";
    if (key & KEY_SELECT) return "SELECT";
    if (key & KEY_START) return "START";

    return "None";
}

bool KeybindsManager::saveToFile(const std::string& filepath) {
    std::filesystem::path path(filepath);
    if (path.has_parent_path()) {
        std::error_code ec;
        std::filesystem::create_directories(path.parent_path(), ec);
    }

    std::ofstream file(filepath, std::ios::binary);
    if (!file.is_open()) return false;

    size_t count = bindings.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& [action, key] : bindings) {
        file.write(reinterpret_cast<const char*>(&action), sizeof(Action));
        file.write(reinterpret_cast<const char*>(&key), sizeof(u32));
    }

    return file.good();
}

bool KeybindsManager::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) return false;

    size_t count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (file.fail()) return false;

    for (size_t i = 0; i < count; ++i) {
        Action action;
        u32 key;
        file.read(reinterpret_cast<char*>(&action), sizeof(Action));
        file.read(reinterpret_cast<char*>(&key), sizeof(u32));

        if (file.fail()) break;
        bindings[action] = key;
    }

    return true;
}