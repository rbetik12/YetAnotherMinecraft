#version 330 core

out vec4 fragColor;

in BLOCK_OUT {
	vec2 texCoord;
} blockOut;

uniform sampler2D blockTexture;

void main() {
	fragColor = texture(blockTexture, blockOut.texCoord);
}