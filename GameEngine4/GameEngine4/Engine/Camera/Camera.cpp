#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()){
	fov = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp = up = glm::vec3(0.0f, 1.0f, 0.0f);
	nPlane = 2.0f;
	fPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	persp = glm::perspective(fov, CoreEngine::GetInstance()->GetWindowSize().x /
		CoreEngine::GetInstance()->GetWindowSize().y, nPlane, fPlane);
	ortho = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f,
		CoreEngine::GetInstance()->GetWindowSize().x,
		-1.0f, 0.0f);

	UpdateCameraVector();

}


Camera::~Camera(){

}

void Camera::SetPosition(glm::vec3 position_){
	position = position_;
	UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_){
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const{

	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPersp() const{

	return persp;
}

glm::mat4 Camera::GetOrtho() const{

	return ortho;
}

void Camera::UpdateCameraVector(){

	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

}
