#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
	Camera();
	~Camera();
	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView()const;
	glm::mat4 GetPersp()const;
	glm::mat4 GetOrtho()const;
private:
	void UpdateCameraVector();
	glm::vec3 position;
	glm::mat4 persp, ortho;
	float fov, yaw, pitch, nPlane, fPlane;
	glm::vec3 forward, up, right, worldUp;
};

#endif