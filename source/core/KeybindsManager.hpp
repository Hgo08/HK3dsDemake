#pragma once

#include <3ds.h>
#include <unordered_map>
#include <string>

enum class Action {
    Up,
    Down,
    Left,
    Right,
    Jump,
    QuickMap,
    Attack,
    SuperDash,
    Dash,
    DreamNail,
    Focus,
    QuickCast,
    Inventory,
    Count
};

class KeybindsManager {
private:
    std::unordered_map<Action, u32> bindings;
    bool isListening = false;
    Action actionBeingRebound = Action::Count;
    u32 normalizeKey(u32 key) const;

    KeybindsManager();

public:
    // Singleton access
    static KeybindsManager& getInstance();

    inline static const std::string SAVE_PATH = "sdmc:/3ds/HK/keybinds.bin";

    // Prevent copy and assignment
    KeybindsManager(const KeybindsManager&) = delete;
    KeybindsManager& operator=(const KeybindsManager&) = delete;

    void setDefaults();
    void startListening(Action action);
    void update();

    bool getIsListening() const;
    Action getActionBeingRebound() const;

    bool isActionPressed(Action action) const;
    bool isActionHeld(Action action) const;

    u32 getBoundKey(Action action) const;
    std::string getKeyName(Action action) const;

    bool saveToFile(const std::string& filepath);
    bool loadFromFile(const std::string& filepath);
};