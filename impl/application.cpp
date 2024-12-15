#include <application.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Application::Application(int width, int height, const char* title)
{
	this->window = nullptr;
	this->width = width;
	this->height = height;
	this->title = title;
	this->isRunning = true;
}

Application::~Application()
{
	glfwTerminate();
}

void Application::fpsCalculate()
{
	static double previousSeconds = glfwGetTime();
	static int frameCount;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		char tmp[128];
		sprintf_s(tmp, "%s @ fps: %.2f, ms/frame: %.2f", title, fps, msPerFrame);
		glfwSetWindowTitle(window, tmp);

		frameCount = 0;
	}

	frameCount++;
}

void Application::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		isRunning = false;
	}
}

void Application::printOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	const GLubyte* vendor = glGetString(GL_VENDOR);

	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;
	std::cout << "GLSL version: " << glslVersion << std::endl;
	std::cout << "Vendor: " << vendor << std::endl;
	std::cout << "Reached application loop..." << std::endl;
	std::cout << "OpenGL initialized successfully!" << std::endl;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Application::run()
{
	std::cout << "Running application and initializing OpenGL..." << std::endl;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ------------------------------------------------------------------------------->>
	// shader manager implementation
	std::cout << "Creating shader program..." << std::endl;
	bool success = true;
	ShaderManager shaderManager;
	success = shaderManager.createShaderProgram();
	if (!success)
	{
		std::cerr << "Failed to create shader program!" << std::endl;
		return;
	}
	success = shaderManager.compileShaders();
	if (!success)
	{
		std::cerr << "Failed to compile shaders!" << std::endl;
		return;
	}
	std::cout << "Shader program created successfully!" << std::endl;

	// ------------------------------------------------------------------------------->>
	// print OpenGL info and use shader program
	printOpenGLInfo();
	shaderManager.useShaderProgram();
	// ------------------------------------------------------------------------------->>
	// coordinate system processing
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	glm::mat4 projection;
	projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	glm::mat4 model = glm::mat4(1.0f);
	// ------------------------------------------------------------------------------->>
	// uniform processing
	unsigned int projectionLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "view");
	unsigned int modelLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "model");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	// ------------------------------------------------------------------------------->>
	// shape setup
	Rectangle rect(glm::vec2(0.0f, 0.0f), glm::vec2(10.0f, 10.0f), glm::vec3(0.9f, 0.8f, 0.5f));
	rect.setupBuffers();
	int count = 0;
	// ------------------------------------------------------------------------------->>
	// loop
	while (!glfwWindowShouldClose(window) && isRunning)
	{
		shaderManager.useShaderProgram();
		fpsCalculate();
		processInput();
		if (rect.position.y < 120) {
			rect.transform(glm::vec2(0.1f, 0.02f));
		}
		std::cout << rect.position.x << " " << rect.position.y << std::endl;
		// clear screen
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// draw rectangles
		rect.draw(modelLoc);
		glfwSwapBuffers(window);
		glfwPollEvents();
		count++;
	}
	// delete stuff
	shaderManager.deleteShaderProgram();
}