#include "Camera.h"

/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::UpdateCamera(float msec){
	//Update the mouse by how much
	pitch -= Mouse::GetRelativePosition().y;
	yaw -= Mouse::GetRelativePosition().x;

	//Bounds check the pitch, to be between straight up and straight down ;)
	pitch = min(pitch, 20.0f);
	pitch = max(pitch, -20.0f);

	yaw = min(yaw, 20.0f);
	yaw = max(yaw, -20.0f);

	//if(yaw < 90) {
	//	yaw += 90.0f;
	//}
	//if(yaw > 90) {
	//	yaw -= 90.0f;
	//}

	if(Keyboard::KeyDown(KEY_D)){
		position += Vector3(0.01f, 0, 0);
	}
	if(Keyboard::KeyDown(KEY_A)){
		position -= Vector3(0.01f, 0, 0);
	}

	if(Keyboard::KeyDown(KEY_W)){
		position += Vector3(0.0f, 0.0f, 0.01f);
	}
	if(Keyboard::KeyDown(KEY_S)){
		position -= Vector3(0.0f, 0.0f, 0.01f);
	}

	//this->position += position * 0.1f;
	//msec *= 5.0f;

	//if(Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_W)){
	//	position += Matrix4::Rotation(yaw, Vector3(0,1,0)) * Vector3(0,0,-1) * msec;
	//}
	////if(Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_S)){
	//	position -= Matrix4::Rotation(yaw, Vector3(0,1,0)) * Vector3(0,0,-1) * msec;
	//}

	//if(Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_A)){
	//	position += Matrix4::Rotation(yaw, Vector3(0,1,0)) * Vector3(-1,0,0) * msec;
	//}
	////if(Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_D)){
	//	position -= Matrix4::Rotation(yaw, Vector3(0,1,0)) * Vector3(-1,0,0) * msec;
	//}

	////if(Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_SHIFT)){
	//	position.y += msec;
	//}
	////if(Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
	//if(Keyboard::KeyDown(KeyboardKeys::KEY_SPACE)){
	//	position.y -= msec;
	//}
}

/*
Generates a view matrix for the camera's viewpoint. This matrix can be sent
straight to the shader...it's already an 'inverse camera' matrix.
*/
Matrix4 Camera::BuildViewMatrix()	{
	//Why do a complicated matrix inversion, when we can just generate the matrix
	//using the negative values ;). The matrix multiplication order is important!
	return	Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * 
		Matrix4::Translation(-position);
};
