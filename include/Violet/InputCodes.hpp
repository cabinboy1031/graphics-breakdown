#ifndef VIOLET_INPUTCODES_H
#define VIOLET_INPUTCODES_H

namespace Violet{
    // Key Codes
// Based off the GLFW keycodes. Some form of conversion system is needed for non GLFW platforms.
    enum KeyCode {
/* The unknown key */
    VGE_KEY_UNKNOWN            = -1,

/* Printable keys */
    VGE_KEY_SPACE              = 32,
    VGE_KEY_APOSTROPHE         = 39,  /* ' */
    VGE_KEY_COMMA              = 44,  /* , */
    VGE_KEY_MINUS              = 45,  /* - */
    VGE_KEY_PERIOD             = 46,  /* . */
    VGE_KEY_SLASH              = 47,  /* / */
    VGE_KEY_0                 = 48,
    VGE_KEY_1                 = 49,
    VGE_KEY_2                 = 50,
    VGE_KEY_3                 = 51,
    VGE_KEY_4                 = 52,
    VGE_KEY_5                 = 53,
    VGE_KEY_6                 = 54,
    VGE_KEY_7                 = 55,
    VGE_KEY_8                 = 56,
    VGE_KEY_9                 = 57,
    VGE_KEY_SEMICOLON          = 59,  /* ; */
    VGE_KEY_EQUAL              = 61,  /* = */
    VGE_KEY_A                  = 65,
    VGE_KEY_B                  = 66,
    VGE_KEY_C                  = 67,
    VGE_KEY_D                  = 68,
    VGE_KEY_E                  = 69,
    VGE_KEY_F                  = 70,
    VGE_KEY_G                  = 71,
    VGE_KEY_H                  = 72,
    VGE_KEY_I                  = 73,
    VGE_KEY_J                  = 74,
    VGE_KEY_K                  = 75,
    VGE_KEY_L                  = 76,
    VGE_KEY_M                  = 77,
    VGE_KEY_N                  = 78,
    VGE_KEY_O                  = 79,
    VGE_KEY_P                  = 80,
    VGE_KEY_Q                  = 81,
    VGE_KEY_R                  = 82,
    VGE_KEY_S                  = 83,
    VGE_KEY_T                  = 84,
    VGE_KEY_U                  = 85,
    VGE_KEY_V                  = 86,
    VGE_KEY_W                  = 87,
    VGE_KEY_X                  = 88,
    VGE_KEY_Y                  = 89,
    VGE_KEY_Z                  = 90,
    VGE_KEY_LEFT_BRACKET       = 91,  /* [ */
    VGE_KEY_BACKSLASH          = 92,  /* \ */
    VGE_KEY_RIGHT_BRACKET      = 93,  /* ] */
    VGE_KEY_GRAVE_ACCENT       = 96,  /* ` */
    VGE_KEY_WORLD_1            = 161, /* non-US #1 */
    VGE_KEY_WORLD_2            = 162, /* non-US #2 */

/* Function keys */
    VGE_KEY_ESCAPE             = 256,
    VGE_KEY_ENTER              = 257,
    VGE_KEY_TAB                = 258,
    VGE_KEY_BACKSPACE          = 259,
    VGE_KEY_INSERT             = 260,
    VGE_KEY_DELETE             = 261,
    VGE_KEY_RIGHT              = 262,
    VGE_KEY_LEFT               = 263,
    VGE_KEY_DOWN               = 264,
    VGE_KEY_UP                 = 265,
    VGE_KEY_PAGE_UP            = 266,
    VGE_KEY_PAGE_DOWN          = 267,
    VGE_KEY_HOME               = 268,
    VGE_KEY_END                = 269,
    VGE_KEY_CAPS_LOCK          = 280,
    VGE_KEY_SCROLL_LOCK        = 281,
    VGE_KEY_NUM_LOCK           = 282,
    VGE_KEY_PRINT_SCREEN       = 283,
    VGE_KEY_PAUSE              = 284,
    VGE_KEY_F1                 = 290,
    VGE_KEY_F2                 = 291,
    VGE_KEY_F3                 = 292,
    VGE_KEY_F4                 = 293,
    VGE_KEY_F5                 = 294,
    VGE_KEY_F6                 = 295,
    VGE_KEY_F7                 = 296,
    VGE_KEY_F8                 = 297,
    VGE_KEY_F9                 = 298,
    VGE_KEY_F10                = 299,
    VGE_KEY_F11                = 300,
    VGE_KEY_F12                = 301,
    VGE_KEY_F13                = 302,
    VGE_KEY_F14                = 303,
    VGE_KEY_F15                = 304,
    VGE_KEY_F16                = 305,
    VGE_KEY_F17                = 306,
    VGE_KEY_F18                = 307,
    VGE_KEY_F19                = 308,
    VGE_KEY_F20                = 309,
    VGE_KEY_F21                = 310,
    VGE_KEY_F22                = 311,
    VGE_KEY_F23                = 312,
    VGE_KEY_F24                = 313,
    VGE_KEY_F25                = 314,
    VGE_KEY_KP_0               = 320,
    VGE_KEY_KP_1               = 321,
    VGE_KEY_KP_2               = 322,
    VGE_KEY_KP_3               = 323,
    VGE_KEY_KP_4               = 324,
    VGE_KEY_KP_5               = 325,
    VGE_KEY_KP_6               = 326,
    VGE_KEY_KP_7               = 327,
    VGE_KEY_KP_8               = 328,
    VGE_KEY_KP_9               = 329,
    VGE_KEY_KP_DECIMAL         = 330,
    VGE_KEY_KP_DIVIDE          = 331,
    VGE_KEY_KP_MULTIPLY        = 332,
    VGE_KEY_KP_SUBTRACT        = 333,
    VGE_KEY_KP_ADD             = 334,
    VGE_KEY_KP_ENTER           = 335,
    VGE_KEY_KP_EQUAL           = 336,
    VGE_KEY_LEFT_SHIFT         = 340,
    VGE_KEY_LEFT_CONTROL       = 341,
    VGE_KEY_LEFT_ALT           = 342,
    VGE_KEY_LEFT_SUPER         = 343,
    VGE_KEY_RIGHT_SHIFT        = 344,
    VGE_KEY_RIGHT_CONTROL      = 345,
    VGE_KEY_RIGHT_ALT          = 346,
    VGE_KEY_RIGHT_SUPER        = 347,
    VGE_KEY_MENU               = 348,

    VGE_KEY_LAST               = VGE_KEY_MENU,
};

    // Mouse codes
    enum MouseButton {
    VGE_MOUSEBUTTON_1         = 0,
    VGE_MOUSEBUTTON_2         = 1,
    VGE_MOUSEBUTTON_3         = 2,
    VGE_MOUSEBUTTON_4         = 3,
    VGE_MOUSEBUTTON_5         = 4,
    VGE_MOUSEBUTTON_6         = 5,
    VGE_MOUSEBUTTON_7         = 6,
    VGE_MOUSEBUTTON_8         = 7,
    VGE_MOUSEBUTTON_LAST      = VGE_MOUSEBUTTON_8,
    VGE_MOUSEBUTTON_LEFT      = VGE_MOUSEBUTTON_1,
    VGE_MOUSEBUTTON_RIGHT     = VGE_MOUSEBUTTON_2,
    VGE_MOUSEBUTTON_MIDDLE    = VGE_MOUSEBUTTON_3,
};

    // TODO Joystick support
    // TODO Gamepad support
    // TODO Gamepad Axis support

}


#endif // VIOLET_INPUTCODES_H
