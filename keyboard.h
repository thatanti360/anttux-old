#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "tetrisos_src/util.h"
#include "tetrisos_src/keyboard.h"
#include "tetrisos_src/irq.h"
#include "tetrisos_src/system.h"
#include "tetrisos_src/timer.h"

// TODO: some of this it 100% wrong lmao xddddddddddd
#define KEY_NULL 0
#define KEY_ESC 27
#define KEY_BACKSPACE '\b'
#define KEY_TAB '\t'
#define KEY_ENTER '\n'
#define KEY_RETURN '\r'

#define KEY_INSERT 0x90
#define KEY_DELETE 0x91
#define KEY_HOME 0x92
#define KEY_END 0x93
#define KEY_PAGE_UP 0x94
#define KEY_PAGE_DOWN 0x95
#define KEY_LEFT 0x4B
#define KEY_UP 0x48
#define KEY_RIGHT 0x4D
#define KEY_DOWN 0x50

#define KEY_F1 0x80
#define KEY_F2 (KEY_F1 + 1)
#define KEY_F3 (KEY_F1 + 2)
#define KEY_F4 (KEY_F1 + 3)
#define KEY_F5 (KEY_F1 + 4)
#define KEY_F6 (KEY_F1 + 5)
#define KEY_F7 (KEY_F1 + 6)
#define KEY_F8 (KEY_F1 + 7)
#define KEY_F9 (KEY_F1 + 8)
#define KEY_F10 (KEY_F1 + 9)
#define KEY_F11 (KEY_F1 + 10)
#define KEY_F12 (KEY_F1 + 11)

#define KEY_LCTRL 0x1D
#define KEY_RCTRL 0x1D

#define KEY_LALT 0x38
#define KEY_RALT 0x38

#define KEY_LSHIFT 0x2A
#define KEY_RSHIFT 0x36

#define KEY_CAPS_LOCK 0x3A
#define KEY_SCROLL_LOCK 0x46
#define KEY_NUM_LOCK 0x45

#define KEY_MOD_ALT 0x0200
#define KEY_MOD_CTRL 0x0400
#define KEY_MOD_SHIFT 0x0800
#define KEY_MOD_CAPS_LOCK 0x1000
#define KEY_MOD_NUM_LOCK 0x2000
#define KEY_MOD_SCROLL_LOCK 0x4000

#define KEYBOARD_RELEASE 0x80

#define KEYBOARD_BUFFER_SIZE 256

#define KEY_IS_PRESS(_s) (!((_s) & KEYBOARD_RELEASE))
#define KEY_IS_RELEASE(_s) (!!((_s) & KEYBOARD_RELEASE))
#define KEY_SCANCODE(_s) ((_s) & 0x7F)
#define KEY_MOD(_s, _m) (!!((_s) & (_m)))
#define KEY_CHAR(_s) __extension__({\
        __typeof__(_s) __s = (_s);\
        KEY_SCANCODE(__s) < 128 ?\
            keyboard_layout_us[KEY_MOD(__s, KEY_MOD_SHIFT) ? 1 : 0][KEY_SCANCODE(__s)] :\
            0;\
    })

struct Keyboard {
    u16 mods;
    bool keys[128];
    bool chars[128];
};

extern u8 keyboard_layout_us[2][128];
extern struct Keyboard keyboard;

#define keyboard_key(_s) (keyboard.keys[(_s)])
#define keyboard_char(_c) (keyboard.chars[(uint8) (_c)])

u8 keyboard_layout_us[2][128] = {
    {
        KEY_NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
        'i', 'o', 'p', '[', ']', KEY_ENTER, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
        'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
        ',', '.', '/', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
        KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
        KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
        KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
    }, {
        KEY_NULL, KEY_ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
        '_', '+', KEY_BACKSPACE, KEY_TAB, 'Q', 'W',   'E', 'R', 'T', 'Y', 'U',
        'I', 'O', 'P',   '{', '}', KEY_ENTER, 0, 'A', 'S', 'D', 'F', 'G', 'H',
        'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
        'M', '<', '>', '?', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4,
        KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
        KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
        KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12
    }
};

struct Keyboard keyboard;

// bad hack! for a better RNG
static bool seeded = false;

static void keyboard_handler(struct Registers *regs) {
    u16 scancode = (u16) inportb(0x60);

    if (!seeded) {
        seed(((u32) scancode) * 17 + timer_get());
        seeded = true;
    }

    if (KEY_SCANCODE(scancode) == KEY_LALT ||
        KEY_SCANCODE(scancode) == KEY_RALT) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_ALT), KEY_IS_PRESS(scancode));
    } else if (
        KEY_SCANCODE(scancode) == KEY_LCTRL ||
        KEY_SCANCODE(scancode) == KEY_RCTRL) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_CTRL), KEY_IS_PRESS(scancode));
    } else if (
        KEY_SCANCODE(scancode) == KEY_LSHIFT ||
        KEY_SCANCODE(scancode) == KEY_RSHIFT) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_SHIFT), KEY_IS_PRESS(scancode));
    } else if (KEY_SCANCODE(scancode) == KEY_CAPS_LOCK) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_CAPS_LOCK), KEY_IS_PRESS(scancode));
    } else if (KEY_SCANCODE(scancode) == KEY_NUM_LOCK) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_NUM_LOCK), KEY_IS_PRESS(scancode));
    } else if (KEY_SCANCODE(scancode) == KEY_SCROLL_LOCK) {
        keyboard.mods = BIT_SET(keyboard.mods, HIBIT(KEY_MOD_SCROLL_LOCK), KEY_IS_PRESS(scancode));
    }

    keyboard.keys[(u8) (scancode & 0x7F)] = KEY_IS_PRESS(scancode);
    keyboard.chars[KEY_CHAR(scancode)] = KEY_IS_PRESS(scancode);
}

void keyboard_init() {
    irq_install(1, keyboard_handler);
}


#endif
