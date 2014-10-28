#include "camera.h"

Camera::Camera(int w, int h, int v) {

	width = w;
	height = h;
	view = v;
	ratio = 1.0f * w / (h);

	vsml = VSMathLib::getInstance();
}

Camera::~Camera() {}

int Camera::getView() {

	return view;
}

void Camera::setView(int v) {

	view = v;
}

void Camera::draw(float camX, float camY, float camZ, float oX, float oY, float oZ) {

	//Ortoghonal projection
	if (view == 1) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		
		if (width > height) {
			vsml->ortho(-ORTHO*ratio, ORTHO*ratio, -ORTHO, ORTHO, -ORTHO, ORTHO + 1);
		}
		else {
			vsml->ortho(-ORTHO, ORTHO, -ORTHO*(1 / ratio), ORTHO*(1 / ratio), -ORTHO, ORTHO + 1);
		}

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(15.5f, ORTHO, 50.0f, 15.5f, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f);
	}

	//Perspective projection
	else if (view == 2) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		vsml->perspective(60.00f, ratio, 0.1f, 1000.0f);

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(15.5f, 55.0f, 50.0f, 15.5f, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f);
	}

	//Chase cam
	else if (view == 3) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		vsml->perspective(50.00f, ratio, 0.1f, 1000.0f);

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(oX - 10.0f, oY + 6.0f, oZ, oX - camX, oY - camY, oZ - camZ, 0.0f, 1.0f, 0.0f);
	}
}