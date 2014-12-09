#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "surface.h"
#include "dynamicObject.h"

class Particles : public DynamicObject {

private:
	typedef struct {
		VSResSurfRevLib *surface;
		float	life;		// vida
		float	fade;		// fade
		GLfloat x, y, z;    // posiçcao
		GLfloat vx, vy, vz; // velocidade 
		GLfloat ax, ay, az; // aceleração
	} Particle;

	Particle particulas[MAX_PARTICULAS];

public:

	Particles(float x, float y, float z);
	~Particles();

	void setupObjects();
	void render(VSShaderLib shader);
	void updateParticles();
	void resetParticles();
};

#endif