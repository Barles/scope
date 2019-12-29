#include "../includes/scope.h"

static const GLfloat mix_buffer[] = {0.5f, 0.5f};

static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

GLuint loadBMP(const char *image_path)
{
	unsigned char header[54];
	unsigned int 	data_pos;
	unsigned int 	width;
	unsigned int 	height;
	unsigned int 	size;
	unsigned char *data;

	FILE * file = fopen(image_path,"rb");
	if (!file){printf("Image could not be opened\n"); return 0;}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return 0;
	}
	if ( header[0]!='B' || header[1]!='M' ){
	    printf("Not a correct BMP file\n");
	    return 0;
	}
	data_pos    = *(int*)&(header[0x0A]);
	size 			 = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	if (size==0)    			size=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (data_pos==0)      data_pos=54; // The BMP header is done that way
	// Create a buffer
	data = malloc(sizeof(unsigned char)* size);
	// Read the actual data from the file into the buffer
	fread(data,1,size,file);
	//Everything is in memory now, the file can be closed
	fclose(file);
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return 1;
}

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
	GLuint		 	colorBuffer;
	GLuint		 	uvBuffer;
  GLuint      mixBuffer;

  t_vec3f *vert;
  t_vec2f *uvs;
  t_vec3f *norm;


	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return -1;
	}


  load_obj("assets/objs/suzanne.obj", &vert, &uvs, &norm);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  printf("test\n");

	win = glfwCreateWindow(1920, 1080, "Scope", NULL, NULL);
  printf("test\n");

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
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	GLfloat g_color_buffer_data[12*3*3];
	for (int v = 0; v < 12*3 ; v++){
	    g_color_buffer_data[3*v+0] = (float) (v*2) / 100.0f;
	    g_color_buffer_data[3*v+1] = (float) (v+2) / 100.0f;
	    g_color_buffer_data[3*v+2] = (float) (v) / 100.0f;
	}

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(g_vertex_buffer_data),
		g_vertex_buffer_data,
		GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(g_color_buffer_data),
		g_color_buffer_data,
		GL_STATIC_DRAW);

  glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(g_uv_buffer_data),
		g_uv_buffer_data,
		GL_STATIC_DRAW);

  glGenBuffers(1, &mixBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mixBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(mix_buffer),
		mix_buffer,
		GL_STATIC_DRAW);

	loadBMP("assets/images/uvtemplate.bmp");

	t_mat4f projection = perspective(
		3.14 / 4.0f,
		1920.0f / 1080.0f,
		0.1f,
		100.0f);

	// projection.m00 = 1.3444;
	// projection.m11 = 1.7925;

	t_mat4f view = lookAt(
		c_vec3f(4.0f,3.0f,3.0f),
		c_vec3f(0.0f,0.0f,0.0f),
		c_vec3f(0.0f,1.0f,0.0f)
	);
	t_mat4f model = init_mat4f(1.0f);
	t_mat4f mvp = mult_mat4f(mult_mat4f(view, projection), model);

	float	**mvp_converted = convert_mat4(mvp);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	GLuint programId = loadShaders("shaders/vertexShader", "shaders/fragmentShader");
	GLuint MatrixID = glGetUniformLocation(programId, "MVP");
	GLuint MixID = glGetUniformLocation(programId, "mixUniform");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// position
	t_vec3f position = c_vec3f( 0, 0, 5 );
	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;
	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
	// Get mouse position
	double lastTime, currentTime;
	double xpos, ypos;
	float FoV = initialFoV;

  float opacityMix = 1.0f;
  int   opacityTrigger = 0;

	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programId);


		currentTime = glfwGetTime();
		float deltaTime = (float)(currentTime - lastTime);
		lastTime = currentTime;
		glfwGetCursorPos(win, &xpos, &ypos);
		// Reset mouse position for next frame
		glfwSetCursorPos(win, 1024/2, 768/2);
		// Compute new orientation
		horizontalAngle += (mouseSpeed * deltaTime * (float)(1024/2 - xpos )) * 100;
		verticalAngle   += (mouseSpeed * deltaTime * (float)( 768/2 - ypos )) * 100;
		t_vec3f direction = c_vec3f(
		    cos(verticalAngle) * sin(horizontalAngle),
		    sin(verticalAngle),
		    cos(verticalAngle) * cos(horizontalAngle)
		);
		t_vec3f right = c_vec3f(
		    sin(horizontalAngle - 3.14f/2.0f),
		    0,
		    cos(horizontalAngle - 3.14f/2.0f)
		);
		t_vec3f up = ft_cross( right, direction );
		// Move forward
		if (glfwGetKey( win, GLFW_KEY_UP ) == GLFW_PRESS){
			position.x += scal_vec3f(direction, deltaTime * speed).x;
			position.y += scal_vec3f(direction, deltaTime * speed).y;
			position.z += scal_vec3f(direction, deltaTime * speed).z;
		}
		// Move backward
		if (glfwGetKey( win, GLFW_KEY_DOWN ) == GLFW_PRESS){
		    position.x -= scal_vec3f(direction, deltaTime * speed).x;
		    position.y -= scal_vec3f(direction, deltaTime * speed).y;
				position.z -= scal_vec3f(direction, deltaTime * speed).z;
		}

		// Move upward
		if (glfwGetKey( win, GLFW_KEY_SPACE ) == GLFW_PRESS){
			position.x += scal_vec3f(up, deltaTime * speed).x;
			position.y += scal_vec3f(up, deltaTime * speed).y;
			position.z += scal_vec3f(up, deltaTime * speed).z;
		}
		// Move downward
		if (glfwGetKey( win, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS){
				position.x -= scal_vec3f(up, deltaTime * speed).x;
				position.y -= scal_vec3f(up, deltaTime * speed).y;
				position.z -= scal_vec3f(up, deltaTime * speed).z;
		}
		// Strafe right
		if (glfwGetKey( win, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		    position.x += scal_vec3f(right, deltaTime * speed).x;
		    position.y += scal_vec3f(right, deltaTime * speed).y;
		    position.z += scal_vec3f(right, deltaTime * speed).z;
		}
		// Strafe left
		if (glfwGetKey( win, GLFW_KEY_LEFT ) == GLFW_PRESS){
		    position.x -= scal_vec3f(right, deltaTime * speed).x;
		    position.y -= scal_vec3f(right, deltaTime * speed).y;
		    position.z -= scal_vec3f(right, deltaTime * speed).z;
		}

		if (glfwGetKey( win, GLFW_KEY_Z ) == GLFW_PRESS && FoV >= 0.00){
			FoV -=  0.05f;
		}
    if (glfwGetKey( win, GLFW_KEY_S ) == GLFW_PRESS) {
			FoV +=  0.05f;
		}

    printf("opacity: %f, trigger: %d\n", opacityMix, opacityTrigger);

    if (glfwGetKey( win, GLFW_KEY_O ) == GLFW_PRESS) {
      if (opacityMix == 0.0f || opacityMix == 1.0f)
      {
        if (opacityTrigger == 0)
        {
          opacityTrigger = 1;
          opacityMix -= 0.01f;
        }
        else
        {
          opacityTrigger = 0;
          opacityMix += 0.01f;
        }
      }
    }

    if (opacityMix < 0.0f)
      opacityMix = 0.0f;
    if (opacityMix > 1.0f)
      opacityMix = 1.0f;


    if (opacityMix > 0.0f && opacityMix < 1.0f)
    {
      if (opacityTrigger == 0)
        opacityMix += 0.01f;
      else
        opacityMix -= 0.01f;
    }

		projection = perspective(
			FoV * (3.14f / 180.0f),
			1920.0f / 1080.0f,
			0.1f,
			100.0f);
		// projection.m00 = 1.3444;
		// projection.m11 = 1.7925;
		// view = lookAt(
		// 	c_vec3f(4.0f,3.0f,3.0f),
		// 	c_vec3f(0.0f,0.0f,0.0f),
		// 	c_vec3f(0.0f,1.0f,0.0f)
		// );
		if (glfwGetKey( win, GLFW_KEY_R ) == GLFW_PRESS) {
			position.x = 4.0f;
			position.y = 4.0f;
			position.z = -4.0f;
			horizontalAngle = -0.78f;
			verticalAngle = -0.62f;
			FoV = 45.0f;
		}
		view = lookAt(
			position,
			a_vec3f(position, direction),
			up
		);
		model = init_mat4f(1.0f);
		mvp = mult_mat4f(mult_mat4f(view, projection), model);
		mvp_converted = convert_mat4(mvp);
		GLfloat final_mvp[4][4] = {
			{mvp_converted[0][0], mvp_converted[0][1], mvp_converted[0][2], mvp_converted[0][3]},
			{mvp_converted[1][0], mvp_converted[1][1], mvp_converted[1][2], mvp_converted[1][3]},
			{mvp_converted[2][0], mvp_converted[2][1], mvp_converted[2][2], mvp_converted[2][3]},
			{mvp_converted[3][0], mvp_converted[3][1], mvp_converted[3][2], mvp_converted[3][3]}
		};
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, *final_mvp);
		glUniform1f(MixID, opacityMix);


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, mixBuffer);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	return 0;
}
