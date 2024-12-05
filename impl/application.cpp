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
	// rectangle array for sorting visualization
	int amount = 4000;
	float rectThickness = 0.04f;
	std::vector<Rectangle> rectangles;
	rectangles.reserve(amount);
	// generate rectangles
	unsigned int modelLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "model");
	for (int i = 0; i < amount; i++) {
		// map 2000 rectangles from -1.0f to 1.0f
		float rnd = static_cast<float>(rand()) / RAND_MAX * 2.0f - 0.8f;
		// random color from 0.0f to 1.0f
		rectangles.emplace_back(glm::vec2(-1.0f, 0.0f), glm::vec2(rectThickness, std::abs(rnd)), glm::vec3(0.0f, 0.0f, 0.0f));  // Ensure positive height
	}
	// Now, place rectangles and account for their height
	for (int i = 0; i < amount; i++) {
		float x = -1.0f + i * 0.0005f;
		// Center each rectangle in the Y direction
		float y = -1.0f + (std::abs(rectangles[i].getSize().y) / 2.0f);
		rectangles[i].resetModelAndSetPosition(glm::vec2(x, y), modelLoc);
	}
	// ------------------------------------------------------------------------------->>
	unsigned int projectionLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "projection");
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && isRunning)
	{
		fpsCalculate();
		processInput();
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		int recRandomOne = rand() % amount;
		int recRandomTwo = rand() % amount;
		float xOne = -1.0f + recRandomOne * 0.0005f;
		float xTwo = -1.0f + recRandomTwo * 0.0005f;
		rectangles[recRandomOne].resetModelAndSetPosition(glm::vec2(xTwo, -1.0f), modelLoc);
		rectangles[recRandomTwo].resetModelAndSetPosition(glm::vec2(xOne, -1.0f), modelLoc);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// draw rectangles
		for (int i = 0; i < amount; i++) {
			rectangles[i].draw(modelLoc);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// delete stuff
	shaderManager.deleteShaderProgram();
}