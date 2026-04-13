typedef struct {
    const char* name;
    WORD value;
} special;
special specials[] = {// add your own just by following the pattern. Make sure the {NULL,0} is at the end otherwise a loop will go out of bounds.
    {"mouseLeft", VK_LBUTTON},    // 0x01 hexadecimal code is valid for windows' INPUT input.ki.wVk property.
    {"mpiseRight", VK_RBUTTON},    // 0x02
  //{"VK_XBUTTON1", VK_XBUTTON1},  // 0x05// mapping for extra mouse button 1 and to. Since this is what we're remapping I don't see the point.
  //{"VK_XBUTTON2", VK_XBUTTON2},  // 0x06
    {"shift", VK_SHIFT},        // 0x10
    {"control", VK_CONTROL},    // 0x11
    {"ctrl", VK_CONTROL},    // 0x11
    {"lcontrol", VK_LCONTROL},  // 0xA2
    {"rcontrol", VK_RCONTROL},
    {"lctrl", VK_LCONTROL},  // 0xA2
    {"rctrl", VK_RCONTROL}, 
    {"alt", VK_MENU},          // 0x12 (Alt)
    {"leftAlt", VK_LMENU},        // 0xA4 (Left Alt)
    {"rightAlt", VK_RMENU},        // 0xA5 (Right Alt)
    {"escape", VK_ESCAPE},      // 0x1B
    {"esc", VK_ESCAPE},      // 0x1B
    {"numpadZero", VK_NUMPAD0},      // 0x0D
    {"F1Key", VK_F1},        // 0x20
    {"tab", VK_TAB},            // 0x09
	{"spacebar", VK_SPACE},
	{"space", VK_SPACE},
	{"caps", VK_CAPITAL},
	{"arrowLeft", VK_LEFT},
	{"arrowRight", VK_RIGHT},
	{"arrowUp", VK_DOWN},
	{"arrowDown", VK_UP},
	{"semicolon", VK_OEM_1},
	{"plus", VK_OEM_PLUS},
	{NULL,0}
};