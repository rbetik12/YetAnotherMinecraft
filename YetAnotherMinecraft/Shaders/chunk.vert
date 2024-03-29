#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 faceColor;
layout (location = 4) in vec2 atlasCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// Assuming that texture size is 256x256 pixels
const float size = 1 / 16.0f;

out BLOCK_OUT {
	vec2 texCoord;
	vec2 atlasCoords;
	vec3 tNormal;
	vec3 fragPos;
} blockOut;

void main() {
	blockOut.fragPos = vec3(model * vec4(position.xyz, 1.0));
	blockOut.texCoord.x = (atlasCoords.x + texCoord.x) * size;
	blockOut.texCoord.y = (atlasCoords.y + (1.0f - texCoord.y)) * size;
	blockOut.atlasCoords = atlasCoords;
	gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
	blockOut.tNormal = mat3(transpose(inverse(model))) * normal;
}
