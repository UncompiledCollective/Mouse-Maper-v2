# Mouse Button Remapper v2
A simple fork of a tool to remap side buttons to any alphanumeric key or a special key like control/alt/shift. Now also allows for mapping both keys at the same time and allows for a reset of mapping.

## Features
   as listed above. This is a fork of another project. 
   You can also add new remappings for more special keys, although I think I've included all the most important ones. 
   See specials.txt to see what input corresponds to a specific special key - for the control key it's either ctrl or control you have to type into the input field to map your mouse button to it. 
   The rest of the description is pretty much just copied from the original. Installation works the same. 

## About
   I'm not a professional so don't expect an S tier code. 
   Special thanks to the original developer Pranjol-Dev, he did most of the work anyway. 
## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Pranjol-Dev/Mouse-Maper.git
    cd Mouse-Maper
    ```

2. **Compile the code:**
    - Make sure you have GCC installed.
    - Run the following command:
    ```bash
    gcc -o Mouse Mouse.c -lgdi32
    ```

3. **Run the executable:**
    ```bash
    ./Mouse
    ```

## Usage

1. **Select Mouse Button:**
    - Click on "Side Button 1" or "Side Button 2" to select which mouse button you want to remap.

2. **Enter Key to Map:**
    - Enter the key you want to map the selected mouse button to in the text box. Either a single letter, for example a or A for the A key
    - For special keys see specials.txt. Input word on the left to the text field to get the specified button on the right to be mapped. 

3. **Set Mapping:**
    - Click "Set Mapping" to apply the remapping.
4. **Reset Mapping:**
    - Click "Reset" to reset mapping of the extra buttons. Resets both of them. 

## Customization

### Changing Colors

If you want to change the colors of the GUI, modify the color definitions in the source code:

```c
#define PASTEL_PINK RGB(255, 182, 193)
#define PASTEL_BLUE RGB(173, 216, 230)
#define PASTEL_GREEN RGB(152, 251, 152)
#define PASTEL_YELLOW RGB(255, 255, 224)
#define PASTEL_PURPLE RGB(216, 191, 216)
```

### Changing Font

To change the font, modify the `CreateFont` call:

```c
HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## Acknowledgments

- Inspired by the need for custom mouse button remapping.
- Uses Windows API for low-level mouse and keyboard interactions.

---

**Developed by [Pranjol Das](https://github.com/Pranjol-Dev)**
```
