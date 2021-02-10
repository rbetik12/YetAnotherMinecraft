#version 330 core

out vec4 fragColor;

in BLOCK_OUT {
	vec2 texCoord;
	vec3 faceColor;
} blockOut;

uniform sampler2D blockTexture;

void main() {
	vec2 texCoord = blockOut.texCoord;
	vec4 texColor = texture(blockTexture, texCoord);
	fragColor = mix(texColor, vec4(blockOut.faceColor, 1.0f), 0.6);
}