# Isometric Optical Illusion Game

[![Build Status](https://travis-ci.org/renaultfernandes/iso-illusion-game.svg?branch=master)](https://travis-ci.org/renaultfernandes/iso-illusion-game)

Beautiful and fun puzzle game based on isometric optical illusions. Developed using OpenGL and C++.

![Screenshot](https://i.imgur.com/WTqUMNf.gif)

## Gameplay

The objective of the game is to move the white sphere onto the colorful flashing tile using the numpad keys 7 (top-left direction), 9 (top-right direction), 1 (bottom-left direction), and 3 (bottom-right direction).

Discover new paths that lead the white sphere to the colorful flashing tile by rotating your view of the game world using the mouse. Rotate the game world by draging the game world from left to right or right to left.

Keys Q/q quits the game and keys R/r restarts the current level.

Enjoy!!!

Inspired by Monument Valley.

## Build

### Dependencies

You'll need to download and install the following to build the game:
- freeglut3
- GCC
- cmake

### Build the game

```
mkdir build && cd build
cmake ..
make
```

## Play

After building, the game binary `iso-illusion-game` will end up in `build/bin/iso-illusion-game`.

```
cd build/bin
./iso-illusion-game
```

## Author

Created by Renault Fernandes.

Cheers!!!
