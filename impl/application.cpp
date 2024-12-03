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
	
	Rectangle rectangleOne(glm::vec2(0.17f, 0.17f), glm::vec2(0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	Rectangle rectangleTwo(glm::vec2(-0.17f, -0.17f), glm::vec2(0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
	Rectangle rectangleThree(glm::vec2(0.17f, -0.17f), glm::vec2(0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f));
	Rectangle rectangleFour(glm::vec2(-0.17f, 0.17f), glm::vec2(0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
	// ------------------------------------------------------------------------------->>

	// ------------------------------------------------------------------------------->>
	unsigned int modelLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "model");
	unsigned int projectionLoc = glGetUniformLocation(shaderManager.getShaderProgram(), "projection");
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && isRunning)
	{
		fpsCalculate();
		processInput();
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= 0.01) {
			glm::vec2 tempPos = rectangleOne.getPosition();
			rectangleOne.setPosition(glm::vec2(tempPos.x + 0.01f, tempPos.y + 0.01f));
			rectangleOne.resetModelAndSetPosition(rectangleOne.getPosition(), modelLoc);
			rectangleTwo.transform(glm::vec2(0.01f, 0.01f));
			rectangleThree.rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			rectangleFour.scaleRect(glm::vec2(0.1f, 0.1f));
			lastTime = currentTime;
		}
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		rectangleOne.draw(modelLoc);
		rectangleTwo.draw(modelLoc);
		rectangleThree.draw(modelLoc);
		rectangleFour.draw(modelLoc);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// delete stuff
	rectangleOne.~Rectangle();
	rectangleTwo.~Rectangle();
	rectangleThree.~Rectangle();
	rectangleFour.~Rectangle();
	shaderManager.deleteShaderProgram();
}