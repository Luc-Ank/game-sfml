# Game SFMF

To run the game(beta): use the commande "make" in the root folder to build. 

To play, just type ./game-sfml in src folder


What you can do :


Move, Collide to monster, Collide to wall in the middle, Collide to dirt tile, Collide to the edge of the map, switch weapon, run, attack monster AND dirt tile with each weapon(and without weapon), kill monster. 


Keybind :


Move up : Up arrow 

Move down : Down arrow

Move left : Left arrow

Move right : Right arrow

Run : x

Switch weapon to dagger/back to no weapon : h

Switch weapon to spear/back to no weapon : g

Attack : v 




## Level editor

### Usage

```level-editor level-filename tile-file```

where :
- `level-filename` is the path the the text file containing the layers of the map (if such a file doesn't exist, it is created)
- `tile-file` is the path to the tile set file. The tiles of this fils have to be 32x32 px, and be organised by lines of 10


### Keys

- `F1` to `F4` select the layer
- `S` save the map
- `R` reload the map from the file
- `F` fill the whole layer
- `Esc` qui the application
- `A`/`Z` increment / decrement the value of life for the layer 4


On the tile seclector window, a left clic will select a tile (the selected one is framed).
On the map window, a left click change the tile of the selected layer. A right clic delete the tile.

To add/remove many tiles at a time, keep `LShift` pressed and keep the left or right button clicked.
>>>>>>> level-editor
