#version 150 core

uniform sampler2D cleanTex;
uniform sampler2D destroyedTex;

uniform float time;

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 fragColour;

void main(void)	{
	//Get clean tex color at current coordinate
	vec4 cleanColor = texture(cleanTex, IN.texCoord);
	//Get destroyed/dirty color at current coordinate
	vec4 destroyedColor = texture(destroyedTex, IN.texCoord);
	
	fragColour = mix(cleanColor, destroyedColor, (1 - 1/time));
}