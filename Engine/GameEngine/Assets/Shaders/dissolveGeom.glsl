#version 150 core

uniform float particleSize;
uniform float time;
 
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
 
in Vertex {
	vec2 texCoord;
	vec4 colour;
} IN[];
 
out Vertex {
	vec2 texCoord;
	vec4 colour;
} OUT;
 
void main(void)	{
	//Get normalized position vector
	vec4 normal = normalize(gl_in[0].gl_Position);
	
	//Update values for first triangle vertex
	OUT.colour = IN[0].colour;
	OUT.texCoord = IN[0].texCoord;
	gl_Position = gl_in[0].gl_Position;
	gl_Position.x += (normal.x * time);
	gl_Position.y += (normal.y * time);
	
	EmitVertex();
	
	//Update values for first triangle vertex
	OUT.colour = IN[1].colour;
	OUT.texCoord = IN[1].texCoord;
	gl_Position = gl_in[1].gl_Position;
	gl_Position.x += (normal.x * time);
	gl_Position.y += (normal.y * time);
	
	EmitVertex();
	
	//Update values for first triangle vertex
	OUT.colour = IN[2].colour;
	OUT.texCoord = IN[2].texCoord;
	gl_Position = gl_in[2].gl_Position;
	gl_Position.x += (normal.x * time);
	gl_Position.y += (normal.y * time);
		
	EmitVertex();

	//Done vertex operations, output triangle
	EndPrimitive();
}