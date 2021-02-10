#pragma once

//That file defines x and y coordinates of cube faces. To define a new texture you should write it's X and Y coordinates on a texture atlas.
// Atlas axis should be oriented like this. Engine loader actually loads atlas texture like this and in fragment shader its y-axis is inverted to be okay with opengl texture standarts.
// (0, 0)------(1, 0)
// |                |
// |                |
// |                |
// |                |
// (0, 1)------(1, 1)

//Mustn't be ever changed!!!
#define BLOCK_FACES_ARRAY_SIZE 12

#define BLOCK_GRAVEL 0, 0
#define BLOCK_STONE 1, 0
#define BLOCK_COBBLESTONE 0, 1
