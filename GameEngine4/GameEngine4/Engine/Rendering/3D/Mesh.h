#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

class Mesh{
public:

	Mesh(std::vector<Vertex>* vertexList_, GLuint shaderProgram_,
		GLuint textureID_);
	~Mesh();
	void Render(Camera* camera_, glm::mat4 transform_);
	
private:
	GLuint shaderProgram;
	void GenerateBuffers();
	GLuint VAO, VBO;
	std::vector<Vertex> vertexList;
	GLuint modelLoc, viewLoc, projLoc, textureID,textureLoc;
};

#endif