#include "../includes/scope.h"

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f
};

void printf_matrix(float **mat)
{
	int i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("[%f]", mat[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

float		**convert_mat4(t_mat4f in)
{
	float	**ret;
	int i = 0;

	ret = malloc(sizeof(float) * 4 * 4);
	while (i < 4)
	{
		ret[i] = malloc(sizeof(float) * 4);
		i++;
	}

	ret[0][0] = in.m00;
	ret[0][1] = in.m01;
	ret[0][2] = in.m02;
	ret[0][3] = in.m03;
	ret[1][0] = in.m10;
	ret[1][1] = in.m11;
	ret[1][2] = in.m12;
	ret[1][3] = in.m13;
	ret[2][0] = in.m20;
	ret[2][1] = in.m21;
	ret[2][2] = in.m22;
	ret[2][3] = in.m23;
	ret[3][0] = in.m30;
	ret[3][1] = in.m31;
	ret[3][2] = in.m32;
	ret[3][3] = in.m33;
	return ret;
}

t_mat4f			init_mat4f(double x)
{
	t_mat4f ret;

	ret.m00 = x;
	ret.m01 = 0.0f;
	ret.m02 = 0.0f;
	ret.m03 = 0.0f;
	ret.m10 = 0.0f;
	ret.m11 = x;
	ret.m12 = 0.0f;
	ret.m13 = 0.0f;
	ret.m20 = 0.0f;
	ret.m21 = 0.0f;
	ret.m22 = x;
	ret.m23 = 0.0f;
	ret.m30 = 0.0f;
	ret.m31 = 0.0f;
	ret.m32 = 0.0f;
	ret.m33 = x;
	return ret;
}

t_mat4f			mult_mat4f(t_mat4f mat1, t_mat4f mat2)
{
	t_mat4f 	ret;

	ret.m00 = mat1.m00 * mat2.m00 + mat1.m01 * mat2.m10 + mat1.m02 * mat2.m20 + mat1.m03 * mat2.m30;
	ret.m01 = mat1.m00 * mat2.m01 + mat1.m01 * mat2.m11 + mat1.m02 * mat2.m21 + mat1.m03 * mat2.m31;
	ret.m02 = mat1.m00 * mat2.m02 + mat1.m01 * mat2.m12 + mat1.m02 * mat2.m22 + mat1.m03 * mat2.m32;
	ret.m03 = mat1.m00 * mat2.m03 + mat1.m01 * mat2.m13 + mat1.m02 * mat2.m23 + mat1.m03 * mat2.m33;

	ret.m10 = mat1.m10 * mat2.m00 + mat1.m11 * mat2.m10 + mat1.m12 * mat2.m20 + mat1.m13 * mat2.m30;
	ret.m11 = mat1.m10 * mat2.m01 + mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31;
	ret.m12 = mat1.m10 * mat2.m02 + mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32;
	ret.m13 = mat1.m10 * mat2.m03 + mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33;

	ret.m20 = mat1.m20 * mat2.m00 + mat1.m21 * mat2.m10 + mat1.m22 * mat2.m20 + mat1.m23 * mat2.m30;
	ret.m21 = mat1.m20 * mat2.m01 + mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31;
	ret.m22 = mat1.m20 * mat2.m02 + mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32;
	ret.m23 = mat1.m20 * mat2.m03 + mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33;

	ret.m30 = mat1.m30 * mat2.m00 + mat1.m31 * mat2.m10 + mat1.m32 * mat2.m20 + mat1.m33 * mat2.m30;
	ret.m31 = mat1.m30 * mat2.m01 + mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31;
	ret.m32 = mat1.m30 * mat2.m02 + mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32;
	ret.m33 = mat1.m30 * mat2.m03 + mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33;
	return ret;
}

t_mat4f			perspective(
	const double fovy,
	const double aspect,
	const double zNear,
	const double zFar)
{
	t_mat4f res;
	double rad;
	double tanHalfFovy;

	res = init_mat4f(0.0f);

	rad = fovy;
	tanHalfFovy = tan(rad / 2.0f);
	res.m00 = 1.0f / (aspect * tanHalfFovy);
	res.m11 = 1.0f / (tanHalfFovy);

	res.m22 = - (zFar + zNear) / (zFar - zNear);
	res.m23 = - 1.0f;
	res.m32 = - (2.0f * zFar * zNear) / (zFar - zNear);
	return res;
}

t_vec3f	ft_cross(t_vec3f x, t_vec3f y)
{
	t_vec3f ret;

	ret.x = x.y * y.z - x.z * y.y;
	ret.y = x.z * y.x - x.x * y.z;
	ret.z = x.x * y.y - x.y * y.x;

	return ret;
}

float ft_inversesqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

// t_vec3f ft_inversesqrt(t_vec3f x)
// {
// 	t_vec3f ret;
// 	t_vec3f x_swap;
//
// 	x_swap = ft_sqrt(x);
//
// 	ret.x = 1 / x_swap.x;
// 	ret.y = 1 / x_swap.y;
// 	ret.z = 1 / x_swap.z;
// 	return ret;
// }

t_vec3f ft_normalize(t_vec3f x)
{
	float sqr = x.x * x.x + x.y * x.y + x.z * x.z;
	return scal_vec3f(x, ft_inversesqrt(sqr));
	// return scal_vec3f(x, (1 / sqrt(sqr)));
}

t_mat4f lookAt
(
	const t_vec3f eye,
	const t_vec3f center,
	const t_vec3f up
)
{
	const t_vec3f f = ft_normalize(s_vec3f(center, eye));
	const t_vec3f s = ft_normalize(ft_cross(f, up));
	const t_vec3f u = ft_cross(s, f);

	t_mat4f res;

	res = init_mat4f(1.0f);
	res.m00 = s.x;
	res.m10 = s.y;
	res.m20 = s.z;
	res.m01 = u.x;
	res.m11 = u.y;
	res.m21 = u.z;
	res.m02 =-f.x;
	res.m12 =-f.y;
	res.m22 =-f.z;
	res.m30 =-dot_vec3f(s, eye);
	res.m31 =-dot_vec3f(u, eye);
	res.m32 = dot_vec3f(f, eye);

	return res;
}

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
	// ft_putstr(vertexShaderCode);
	// ft_putstr(fragmentShaderCode);


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
	if ( InfoLogLength > 0 ){
		char *VertexShaderErrorMessage = malloc(sizeof(char) * InfoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragmentFile);
	char const * FragmentSourcePointer = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char *FragmentShaderErrorMessage = malloc(sizeof(char) * InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		char *ProgramErrorMessage = malloc(sizeof(char) * InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
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

	t_mat4f projection = perspective(
		// 0.785f,
		3.14 / 4.0f,
		// 4.0f / 3.0f,
		1024.0f / 768.0f,
		0.1f,
		100.0f);

	projection.m00 = 1.3444;
	projection.m11 = 1.7925;

	t_mat4f view = lookAt(
		c_vec3f(4.0f,3.0f,3.0f),
		c_vec3f(0.0f,0.0f,0.0f),
		c_vec3f(0.0f,1.0f,0.0f)
	);
	t_mat4f model = init_mat4f(1.0f);
	t_mat4f mvp = mult_mat4f(mult_mat4f(view, projection), model);
	// t_mat4f mvp = mult_mat4f(mult_mat4f(projection, view), model);

	float	**projection_c = convert_mat4(projection);
	float	**view_c = convert_mat4(view);
	float	**model_c = convert_mat4(model);
	float	**mvp_converted = convert_mat4(mvp);

	printf_matrix(projection_c);
	printf("====================\n");
	printf_matrix(view_c);
	printf("====================\n");
	printf_matrix(model_c);
	printf("====================\n");
	printf_matrix(mvp_converted);
	printf("====================\n");

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	GLuint programId = loadShaders("shaders/vertexShader", "shaders/fragmentShader");
	GLuint MatrixID = glGetUniformLocation(programId, "MVP");

	const GLfloat test_mvp[4][4] = {
		{mvp_converted[0][0], mvp_converted[0][1], mvp_converted[0][2], mvp_converted[0][3]},
		{mvp_converted[1][0], mvp_converted[1][1], mvp_converted[1][2], mvp_converted[1][3]},
		{mvp_converted[2][0], mvp_converted[2][1], mvp_converted[2][2], mvp_converted[2][3]},
		{mvp_converted[3][0], mvp_converted[3][1], mvp_converted[3][2], mvp_converted[3][3]}
	};

	// t_mat4f test = init_mat4f(1.0f);
	// float **test_c = convert_mat4(test);
	// glGetUniformfv(programId, MatrixID, *test_c);
	// printf_matrix(test_c);
	// printf("%f\n", test_c[0][0]);

	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programId);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, *test_mvp);

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
