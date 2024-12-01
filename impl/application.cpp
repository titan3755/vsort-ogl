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

	// ------------------------------------------------------------------------------->>
	// rectangle implementation
	// middle rectangles
	Rectangle rect(glm::vec2(-0.5f, 0.0f), glm::vec2(0.25f, 0.25f), glm::vec3(0.12f, 0.8f, 0.5f));
	Rectangle rectOne(glm::vec2(0.0f, 0.0f), glm::vec2(0.25f, 0.25f), glm::vec3(0.6f, 0.4f, 0.3f));
	Rectangle rectTwo(glm::vec2(0.5f, 0.0f), glm::vec2(0.25f, 0.25f), glm::vec3(0.3f, 0.4f, 0.6f));
	// lower rectangles
	Rectangle rectThree(glm::vec2(-0.5f, -0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.8f, 0.2f, 0.5f));
	Rectangle rectFour(glm::vec2(0.0f, -0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.5f, 0.2f, 0.8f));
	Rectangle rectFive(glm::vec2(0.5f, -0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.8f, 0.5f, 0.2f));
	// upper rectangles
	Rectangle rectSix(glm::vec2(-0.5f, 0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.665f, 0.2555f, 0.8f));
	Rectangle rectSeven(glm::vec2(0.0f, 0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.46f, 0.8f, 0.9f));
	Rectangle rectEight(glm::vec2(0.5f, 0.5f), glm::vec2(0.25f, 0.25f), glm::vec3(0.9f, 0.2f, 0.1f));
	// ------------------------------------------------------------------------------->>

	while (!glfwWindowShouldClose(window) && isRunning)
	{
		fpsCalculate();
		processInput();
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderManager.useShaderProgram();
		rect.draw();
		rectOne.draw();
		rectTwo.draw();
		rectThree.draw();
		rectFour.draw();
		rectFive.draw();
		rectSix.draw();
		rectSeven.draw();
		rectEight.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// delete stuff
	rect.~Rectangle();
	rectOne.~Rectangle();
	rectTwo.~Rectangle();
	rectThree.~Rectangle();
	rectFour.~Rectangle();
	rectFive.~Rectangle();
	rectSix.~Rectangle();
	rectSeven.~Rectangle();
	rectEight.~Rectangle();
	shaderManager.deleteShaderProgram();
}