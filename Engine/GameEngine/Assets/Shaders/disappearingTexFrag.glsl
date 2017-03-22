#version 150 core

uniform sampler2D cleanTex;

uniform float time;

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 fragColour;

void main(void)	{
	//Get tex color at current coordinate
	vec4 cleanColor = texture(cleanTex, IN.texCoord);
	
	//decrease the alpha value of the texture over time
	//until reaching 30s (without it would approach 0 without ever getting there)
	cleanColor.a = time < 30 ? 1/time : 0;
	
	fragColour = cleanColor;
}