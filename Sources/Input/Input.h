#pragma once

#include <vector>

enum class Keycode {
    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    Alpha1 = 30,
    Alpha2 = 31,
    Alpha3 = 32,
    Alpha4 = 33,
    Alpha5 = 34,
    Alpha6 = 35,
    Alpha7 = 36,
    Alpha8 = 37,
    Alpha9 = 38,
    Alpha0 = 39,

    Return = 40,
    Escape = 41,
    Backspace = 42,
    Tab = 43,
    Space = 44,

    Minus = 45,
    Equals = 46,
    LeftBracket = 47,
    RigthBracket = 48,

    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,

    Semicolon = 51,
    Apostrophe = 52,
    Grave = 53,

    PrintScreen = 70,
    ScrollLock = 71,
    Pause = 72,
    Insert = 73,
    Home = 74,
    PgUp = 75,
    Delete = 76,
    End = 77,
    PgDown = 78,
    ArrowRight = 79,
    ArrowLeft = 80,
    ArrowDown = 81,
    ArrowUp = 82,

    NumDivide = 84,
    NumMultiply = 85,
    NumMinus = 86,
    NumPlus = 87,
    NumEnter = 88,
    Num1 = 89,
    Num2 = 90,
    Num3 = 91,
    Num4 = 92,
    Num5 = 93,
    Num6 = 94,
    Num7 = 95,
    Num8 = 96,
    Num9 = 97,
    Num0 = 98,
    NumPeriod = 99,
    NumEquals = 103,

    LeftControl = 224,
    LeftShift = 225,
    LeftAlt = 226,
    LeftSuper = 227,
    RightControl = 228,
    RightShift = 229,
    RightAlt = 230,
    RightSuper = 231,
};

class Input {
private:

    static constexpr size_t cKeyCount = 256;

    static std::vector<int> mPressedKeys;

public:
    static void Init() {
        mPressedKeys = std::vector<int>(cKeyCount);

        for (auto& value : mPressedKeys) {
            value = 0;
        }
    }

    inline static bool getKey(Keycode keycode) {
        return bool(mPressedKeys[static_cast<int>(keycode)]);
    }

    inline static void setKey(Keycode keycode, bool value) {
        mPressedKeys[static_cast<int>(keycode)] = bool(value);
    }

};