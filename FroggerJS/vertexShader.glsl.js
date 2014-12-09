var vertexShaderSrc =

	"uniform mat4 m_pvm;" +
	"uniform mat4 m_viewModel;" +
	"uniform mat3 m_normal;" +

	"attribute vec4 vertexPosition;" +
	"attribute vec3 vertexNormal;" + 
	"attribute vec2 texCoordinates;" +
	
	"varying vec3 normal;" +
	"varying vec2 texCoord;" +
	"varying vec4 position;" +
	"varying vec4 eye;" +
	
	"void main (void) {" +

		"eye = m_viewModel*vertexPosition;" +
		"normal = normalize(m_normal * vertexNormal);" +
		"position = m_viewModel * vertexPosition;" +
		"texCoord = texCoordinates;" +
		"gl_Position = m_pvm* vertexPosition;" +
	"}";
