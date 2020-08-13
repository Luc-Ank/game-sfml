# Game SFMF




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
- `Esc` qui the application

On the tile seclector window, a left clic will select a tile (the selected one is framed).
On the map window, a left click change the tile of the selected layer. A right clic delete the tile.