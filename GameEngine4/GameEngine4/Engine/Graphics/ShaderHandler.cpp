#include "ShaderHandler.h"

std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
std::map < std::string, GLuint> ShaderHandler::programs =
std::map < std::string, GLuint>();

void ShaderHandler::CreateProgram(const std::string & shaderName_,
	const std::string & vertexShanderFileName_,
	const std::string & fragmentShanderFileName_){
	std::string vertexShaderCode = ReadShader(vertexShanderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShanderFileName_);

	if (vertexShaderCode == "" || fragmentShaderCode == "")return;

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER,vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);
	if (vertexShader == 0 || fragmentShader == 0)return;

	GLint LinkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &LinkResult);

	if (!LinkResult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		Debug::Error("Failed to link shader:" + shaderName_ +  "Error" + programString,
			"ShaderHandler.cpp", __LINE__);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(program);
		return;
	}

	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const std::string & shaderName_){
	if (programs.find(shaderName_) != programs.end()) {
		return programs[shaderName_];
	}

	return 0;
}

void ShaderHandler::OnDestroy(){
	for (auto p : programs) {
		glDeleteProgram(p.second);
	}
	programs.clear();
}

ShaderHandler::ShaderHandler(){

}


ShaderHandler::~ShaderHandler(){
	OnDestroy();

}

std::string ShaderHandler::ReadShader(const std::string & filePath_){
	std::string shaderCode = "";
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try {
		file.open(filePath_);
		std::stringstream tmpStream;
		tmpStream << file.rdbuf();
		file.close();
		shaderCode = tmpStream.str();
	}
	catch (std::ifstream::failure error_) {
		Debug::Error("Could not read shader:" + filePath_, "ShaderHadler.cpp", __LINE__);

	}

	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_,
	const std::string & source_, const std::string & shaderName_){

	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCodePtr = source_.c_str();
	const int shaderCodeSize = source_.size();
	

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog (infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::Error(shaderString, "", 0);
		return 0;
	}

	return shader;
}

ShaderHandler * ShaderHandler::GetInstance(){

	if (shaderInstance.get() == nullptr) {

		shaderInstance.reset(new ShaderHandler);

	}
	return shaderInstance.get();
}
