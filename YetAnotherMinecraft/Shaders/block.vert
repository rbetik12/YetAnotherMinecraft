#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform uint textureIds[12];

const float size = 1 / 16.0f;

out BLOCK_OUT {
	vec2 texCoord;
} blockOut;

void main() {
	blockOut.texCoord.x = (textureIds[int(position.w)] + texCoord.x) * size;
	blockOut.texCoord.y = (textureIds[int(position.w) + 1] + texCoord.y) * size;
	gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
}
