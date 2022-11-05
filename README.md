<img align="left" width="100" height="100" src="https://i.imgur.com/IlTprgN.png">  

# PopSpriteEditor
Open source Sprite Viewer &amp; Editor tool written in C++/CLI for Bullfrog's **Populous: The Beginning** game.

<p align="center">
 <img width="800" height="600" src="https://i.imgur.com/XMEdjnT.png"></img>
</p>

### Features
- **Open banks**:
  - Preview scaled sprites (slider) with nearest-neighbor interpolation.
  - Export sprites as bitmaps (individually or in bulk).
  - View offset, index, width, height and raw data of each sprite.
- **Create banks**:
  - From bitmaps of any width & height.
  - Append or insert to an "existing" bank.
  - Modify original sprites width & height.
- **Color Palette**:
  - Preview color palette.
  - Adjustable color key.
  - Export to bitmap format.
- **Pixel Inspector**; hover over an image and a tooltip will appear showing the highlighted pixel's values:
	- Position (current width & height).
	- RGB values.
	- Index in the color palette.
	- Right click to copy RGB values.
- **Sprite Editor**:
	- 2 color slots (right/left click).
	- Brush mode; paint individual pixels (r/l click).
	- Color pick mode; copy RGB values from highlighted pixel (r/l click).
	- ``CTRL + Z`` (undo).
	- ``CTRL + Y`` (redo).
	- Key ``B`` (brush mode).
	- Key ``Y`` (color pick mode).
- **Sprite Sheet Manager**:
	- Generate sheets from frames.
	- Parse & Split sheets to individual frames.
  
### Usage
Usage is straight forward. The numbering (names) of the bitmaps is the order they'll be saved in, and any gaps in the numbering isn't a problem as the editor will renumber the files internally. Files that aren't bitmaps or bitmaps with letters in the name will be ignored.
1. Download the latest release from [here](https://github.com/Toksisitee/PopSpriteEditor/releases).
2. Ensure `pal.dat` is located in the same folder as the software.
3. Open a valid bank `File` -> `Open` from the game's `data` folder.
4. Export all sprites within the bank `File` -> `Export Sprites`.
5. Open the newly created folder `output` (editor folder), it should contain all saved sprites.
6. Modify (resolution and/or colors), delete or add new bitmaps.
7. Create a new bank from these bitmaps `File` -> `Create Sprite Bank` -> `From Images`.
8. Replace the original game's sprite bank with the newly created one.

### Sprite Sheets
A valid sprite sheet has to abide by the following rules:
* Sprites can't touch corners or edges; ensure there's a space between of at least 1 pixel.
* New rows have to be separated by a pink continuous line.
* Background color has to be cyan. (RGB: 0, 255, 255)
* Color key color has to be pink. (RGB: 255, 0, 255)

An example of a valid sprite sheet:  
![valid sprite sheet](https://i.imgur.com/TAhdfqI.png)

### Credits
[EasyBMP Library](http://easybmp.sourceforge.net/about.html)

### License
PopSpriteEditor Copyright © 2020 Toksisitee.  
This program is distributed under the GNU GPLv3 license. See the LICENSE file for more details. 
