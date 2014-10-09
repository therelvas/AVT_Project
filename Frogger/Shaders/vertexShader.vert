#version 330 core

layout (std140) uniform Matrices {
	mat4 pvm;
};

in vec4 in_Position;	
out vec4 color;

void main(void)
{
	color = in_Position;
	gl_Position = pvm * in_Position;

}