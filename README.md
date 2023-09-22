# Cub3D | Wolfenstein3d Inspired | 42Paris
A 3D game using self-implemented Wolfenstein's ray casting algorithm, allowing players to navigate through an immersive environment 
with textured walls and interactive objects.

## Introduction
In this project we are asked to extract information from a .cub file and use that information to draw a 3d maze on the screen using 
raycasting principles.

## Usage
This project was designed to be run using minilibx-linux. Ensure you have the correct libraries installed. If you are using Macos some updates may be needed
on the Makefile and the code itself. To start:
- git clone https://github.com/shimazadeh/Cub3D.git Cub3D
- cd Cub3D && make
- to start the game: ./cub3D map.cub
- You may change or adjust the textures inside the texture folder as well as the map itself, the color of the ceiling/floor to your preference.
- Use w,a,d and s keys on the keyboard to move foward, left, right and backward respectively.
- Use right and left arrows to move the field of view to right and left respectively.
  
## Basic Demo

https://github.com/shimazadeh/Cub3D/assets/67879533/20551dbb-9a41-4d98-b90f-7ba7e7e03448


## Sources
Here are the sources I used that helped me to figure out a lot:
- https://harm-smits.github.io/42docs/libs/minilibx
- https://harm-smits.github.io/42docs/projects/cub3d
- Pikuma Javascript Raycasting Introduction
