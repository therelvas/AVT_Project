#ifndef WOOD_H
#define WOOD_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"


#include "dynamicObject.h"

class Wood : public DynamicObject {

private:

	VSResSurfRevLib *vsres[3];

public:

	Wood(float x, float y, float z);
	~Wood();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);

	virtual void move(float x, float y, float z, float speed);
	
	virtual float** getBoundingBox();
	virtual void collide(DynamicObject* frog);
};

#endif