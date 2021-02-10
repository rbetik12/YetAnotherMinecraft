#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 faceColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec2 blockAtlasCoords[6];

const float size = 1 / 16.0f;

out BLOCK_OUT {
	vec2 texCoord;
	vec3 faceColor;
} blockOut;

void main() {
	blockOut.texCoord.x = (blockAtlasCoords[int(position.w)].x + texCoord.x) * size;
	blockOut.texCoord.y = (blockAtlasCoords[int(position.w)].y + (1.0f - texCoord.y)) * size;
	//blockOut.faceColor = faceColor;
	gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
}
