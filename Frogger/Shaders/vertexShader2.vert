#version 330 core

	in vec4 in_Position;	
	uniform mat4 pvm;
	out vec4 color;

	void main(void)
	{
		color = in_Position;
		gl_Position = pvm * in_Position;

	}