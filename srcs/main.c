#include "../includes/scope.h"

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f
};

GLuint	loadShaders(const char *vertexFile, const char *fragmentFile)
{
	GLuint	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	int			vertexFd;
	int			fragmentFd;
	char 		*vertexShaderCode;
	char 		*fragmentShaderCode;
	char		*line;
	vertexShaderCode = ft_strnew(0);
	fragmentShaderCode = ft_strnew(0);

	vertexFd = open(vertexFile, O_RDONLY);
	while (get_next_line(vertexFd, &line) > 0)
	{
		vertexShaderCode = ft_strjoin(vertexShaderCode, ft_strjoin(line, "\n"));
	}
	free(line);

	fragmentFd = open(fragmentFile, O_RDONLY);
	while (get_next_line(fragmentFd, &line) > 0)
	{
		fragmentShaderCode = ft_strjoin(fragmentShaderCode, ft_strjoin(line, "\n"));
	}
	free(line);
	ft_putstr(vertexShaderCode);
	ft_putstr(fragmentShaderCode);


	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexFile);
	char const * VertexSourcePointer = vertexShaderCode;
	glShaderSource(vertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	// if ( InfoLogLength > 0 ){
	// 	std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
	// 	glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	// 	printf("%s\n", &VertexShaderErrorMessage[0]);
	// }

	// Compile Fragment Shader
printf("Compiling shader : %s\n", fragmentFile);
char const * FragmentSourcePointer = fragmentShaderCode;
glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , NULL);
glCompileShader(fragmentShaderID);

// Check Fragment Shader
glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
// if ( InfoLogLength > 0 ){
// 	std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
// 	glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
// 	printf("%s\n", &FragmentShaderErrorMessage[0]);
// }

// Link the program
printf("Linking program\n");
GLuint ProgramID = glCreateProgram();
glAttachShader(ProgramID, vertexShaderID);
glAttachShader(ProgramID, fragmentShaderID);
glLinkProgram(ProgramID);
// Check the program
glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
// if ( InfoLogLength > 0 ){
// 	std::vector<char> ProgramErrorMessage(InfoLogLength+1);
// 	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
// 	printf("%s\n", &ProgramErrorMessage[0]);
// }

glDetachShader(ProgramID, vertexShaderID);
glDetachShader(ProgramID, fragmentShaderID);

glDeleteShader(vertexShaderID);
glDeleteShader(fragmentShaderID);

return ProgramID;

	return 1;
}

int			main(void)
{
	GLFWwindow	*win;
	GLuint			vertexArrayID;
	GLuint			vertexBuffer;


	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win = glfwCreateWindow(1024, 768, "Scope", NULL, NULL);
	if (win == NULL) {
		fprintf(stderr, "Failed to open GLFW Window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(g_vertex_buffer_data),
		g_vertex_buffer_data,
		GL_STATIC_DRAW);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	GLuint programId = loadShaders("shaders/vertexShader", "shaders/fragmentShader");

	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programId);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	return 0;
}
