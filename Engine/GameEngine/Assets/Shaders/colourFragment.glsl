#version 150 core

in Vertex {
	vec4 colour;
} IN;

out vec4 frag;

void main(void){
	frag = IN.colour;
}