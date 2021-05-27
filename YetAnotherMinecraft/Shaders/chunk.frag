#version 330 core

out vec4 fragColor;

in BLOCK_OUT {
	vec2 texCoord;
	vec2 atlasCoords;
	vec3 tNormal;
	vec3 fragPos;
} blockOut;

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;
uniform sampler2D blockTexture;
uniform vec3 viewPos;

void main() {
	vec2 texCoord = blockOut.texCoord;
	vec4 texColor = texture(blockTexture, texCoord);
	vec3 ambient = directionalLight.ambient * texColor.rgb;

	vec3 norm = normalize(blockOut.tNormal);
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = directionalLight.diffuse * diff;

	vec3 viewDir = normalize(viewPos - blockOut.fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * directionalLight.specular; 
	
	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, texColor.a);
}