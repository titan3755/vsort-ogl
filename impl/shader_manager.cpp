#include <shader_manager.h>

ShaderManager::ShaderManager()
{
	this->vertexShaderSource = nullptr;
	this->fragmentShaderSource = nullptr;
	this->shaderProgram = 0;
}

ShaderManager::~ShaderManager()
{
	deleteShaderProgram();
}

bool ShaderManager::createShaderProgram()
{
	shaderProgram = glCreateProgram();
	return shaderProgram != 0;
}

const std::string ShaderManager::shaderReaderFromFile(const char* shaderPath)
{
	std::ifstream shaderFile(shaderPath);
	if (!shaderFile.is_open())
	{
		std::cerr << "Failed to open file: " << shaderPath << std::endl;
		return "";
	}

	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	return shaderStream.str();
}


bool ShaderManager::shaderWriterToFile(const char* shaderPath, const char* shaderSource)
{
	std::ofstream shaderFile;
	shaderFile.open(shaderPath);
	if (!shaderFile.is_open())
	{
		std::cerr << "Failed to open file: " << shaderPath << std::endl;
		return false;
	}
	shaderFile << shaderSource;
	shaderFile.close();
	return true;
}

bool ShaderManager::compileShaders()
{
    std::string vertexShaderSourceStr = shaderReaderFromFile(vertexShaderPath);
    std::string fragmentShaderSourceStr = shaderReaderFromFile(fragmentShaderPath);

    if (vertexShaderSourceStr.empty() || fragmentShaderSourceStr.empty())
    {
        return false;
    }

    const char* vertexShaderSource = vertexShaderSourceStr.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceStr.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
        return false;
    }
	std::cout << "--------------------------------------\n";
	std::cout << "Vertex shader source: \n" << vertexShaderSource << "\n\n";
	std::cout << "--------------------------------------\n";

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
        return false;
    }

	std::cout << "--------------------------------------\n";
	std::cout << "Fragment shader source: \n" << fragmentShaderSource << "\n\n";
	std::cout << "--------------------------------------\n";

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}


void ShaderManager::useShaderProgram()
{
	glUseProgram(shaderProgram);
}

unsigned int ShaderManager::getShaderProgram()
{
	return shaderProgram;
}

void ShaderManager::deleteShaderProgram()
{
	glDeleteProgram(shaderProgram);
}




