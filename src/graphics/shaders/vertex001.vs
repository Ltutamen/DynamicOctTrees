#version 320 es

layout (location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;
uniform mat4 projection;

void main(){

	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1.0);
	//  projection;
}