#include "tree.h"

Tree::Tree(float x, float y, float z) : StaticObject(x, y, z) {
	
	billboard = new Surface();
	setupObjects();
}

void Tree::setupObjects(){

	vectorOrientation[0] = 1.0f;
	vectorOrientation[1] = 0.0f;
	vectorOrientation[2] = 0.0f;

	float body_amb[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float body_diff[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float body_spec[] = { 0.0f, 1.0f, 0.0f, 1.0f };

	//Tree
	billboard->addTexture(0, "assets/tree.tga");
	billboard->setColor(VSResourceLib::AMBIENT, body_amb);
	billboard->setColor(VSResourceLib::DIFFUSE, body_diff);
	billboard->setColor(VSResourceLib::SPECULAR, body_spec);
}

void Tree::render(VSShaderLib shader){
	
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);

	vsml->translate(position[0], position[1], position[2]);
	
	if ((angle < 0.99990) && (angle > -0.9999))
		vsml->rotate(acos(-angle) * 180.0f / 3.14f, auxVector[0], auxVector[1], auxVector[2]);

	vsml->scale(1.0f, 10.0f, 8.0f);
	billboard->render(shader);
	
	vsml->popMatrix(VSMathLib::MODEL);
}

void Tree::updateRotation(float* frogPos){
	
	vector[0] = frogPos[0] - position[0];
	vector[1] = 0.0f;
	vector[2] = frogPos[2] - position[2];

	vsml->normalize(vector);
	vsml->crossProduct(vector, vectorOrientation, auxVector);
	angle = vsml->dotProduct(vector, vectorOrientation);
}