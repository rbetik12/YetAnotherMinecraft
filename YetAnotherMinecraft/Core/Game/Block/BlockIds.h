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

//For a chunk system atlas coordinates must be defined separately
#define BLOCK_STONE_X 1
#define BLOCK_STONE_Y 0

#define BLOCK_GRAVEL_X 0
#define BLOCK_GRAVEL_Y 0

#define BLOCK_COBBLESTONE_X 0
#define BLOCK_COBBLESTONE_Y 1

#define BLOCK_IRON_ORE_X 1
#define BLOCK_IRON_ORE_Y 2

#define BLOCK_DIRT_X 2
#define BLOCK_DIRT_Y 0

#define BLOCK_GRAVEL BLOCK_GRAVEL_X, BLOCK_GRAVEL_Y
#define BLOCK_STONE BLOCK_STONE_X, BLOCK_STONE_Y
#define BLOCK_COBBLESTONE BLOCK_COBBLESTONE_X, BLOCK_COBBLESTONE_Y

enum BlockType {
    Empty,
    Gravel,
    Stone,
    IronOre,
    Dirt,
    Cobblestone
};
