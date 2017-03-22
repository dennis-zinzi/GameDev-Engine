#version 400 core

uniform sampler2D destroyedTex;

in Vertex {
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main(){
	fragColor = texture(destroyedTex, IN.texCoord);
}