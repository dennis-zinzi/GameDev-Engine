#version 150 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

in vec2 texCoord;
in vec3 position;
in vec4 colour;

uniform mat4 transforms[5];

out Vertex{
	vec2 texCoord;
	vec4 colour;
} OUT;


void main(){
	OUT.texCoord = texCoord;
	OUT.colour = vec4(0.5, 0.5, 0.5, 1.0);
	
	int nodeA = int(colour[0]);
	int nodeB = int(colour[1]);
	
	float weightA = colour[2];
	float weightB = colour[3];
	
	vec4 posA = (transforms[nodeA] * vec4(position, 1)) * weightA;
	vec4 posB = (transforms[nodeB] * vec4(position, 1)) * weightB;
	
	vec4 finalPos = posA + posB;
	
	gl_Position = (projMatrix * viewMatrix * modelMatrix) * vec4(finalPos.xyz, 1);
}