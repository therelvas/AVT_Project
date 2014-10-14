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

void Camera::draw(float x, float y, float z) {

	//Ortoghonal projection
	if (view == 1) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		
		if (width > height) {
			vsml->ortho(-ORTHO*ratio, ORTHO*ratio, -ORTHO, ORTHO, -ORTHO, ORTHO);
		}
		else {
			vsml->ortho(-ORTHO, ORTHO, -ORTHO*(1 / ratio), ORTHO*(1 / ratio), -ORTHO, ORTHO);
		}

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(15.0f, 20.0f, 0.0f, 15.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	}

	//Perspective projection
	else if (view == 2) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		vsml->perspective(50.00f, ratio, 0.1f, 1000.0f);

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(-30.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}

	//Temporary settings
	else if (view == 3) {

		vsml->loadIdentity(VSMathLib::PROJECTION);
		vsml->perspective(50.00f, ratio, 0.1f, 1000.0f);

		vsml->loadIdentity(VSMathLib::VIEW);
		vsml->loadIdentity(VSMathLib::MODEL);

		vsml->lookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
}