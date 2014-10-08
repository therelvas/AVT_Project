// PRIVATE METHODS

/*
char * textFileRead(std::string fileName) {


	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fileName != "") {
		fp = fopen(fileName.c_str(), "rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}


void createShaderProgram()
	{
		char *vs;

		// get a shader handler
		VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		// read the shader source from a file
		vs = textFileRead("../vertexShader.vert");
		// conversions to fit the next function
		const char *VertexShader = vs;
		// pass the source text to GL
		glShaderSource(VertexShaderId, 1, &VertexShader, 0);
		// free the memory from the source text
		free(vs);
		// finally compile the shader
		glCompileShader(VertexShaderId);

		char *fs;

		// get a shader handler
		FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		// read the shader source from a file
		fs = textFileRead("../fragmentShader.frag");
		// conversions to fit the next function
		const char *FragmentShader = fs;
		// pass the source text to GL
		glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
		// free the memory from the source text
		free(fs);
		// finally compile the shader
		glCompileShader(FragmentShaderId);

		ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);

		glBindAttribLocation(ProgramId, VERTEX_COORD_ATTRIB, "in_Position");

		glLinkProgram(ProgramId);
		UniformId = glGetUniformLocation(ProgramId, "Matrix");

		checkOpenGLError("ERROR: Could not create shaders.");
	}
	return content;
}*/