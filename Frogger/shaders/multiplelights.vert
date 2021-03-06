#version 330

uniform	mat4 m_pvm;
uniform	mat4 m_viewModel;
uniform	mat3 m_normal;

in vec4 vertexPosition;
in vec4 vertexNormal;    //por causa do gerador de geometria
in vec2 texCoord;

out Data {
	vec3 normal;
	vec2 texCoord;
	vec4 position;
	vec4 eye;
} DataOut;

void main () {

	DataOut.eye = m_viewModel*vertexPosition;
	DataOut.normal = normalize(m_normal * vertexNormal.xyz);
	DataOut.position = m_viewModel * vertexPosition;
	DataOut.texCoord = texCoord;
	gl_Position = m_pvm * vertexPosition;	
}