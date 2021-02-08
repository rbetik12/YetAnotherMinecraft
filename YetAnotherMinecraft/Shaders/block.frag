#version 330 core

out vec4 fragColor;

in BLOCK_OUT {
	vec2 texCoord;
} blockOut;

void main() {
	fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}