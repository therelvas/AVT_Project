#include "particles.h"

Particles::Particles(float x, float y, float z) : DynamicObject(x, y, z) {

	setupObjects();
}

Particles::~Particles(){}

void Particles::setupObjects() {
	
	GLfloat v, theta, phi;

	float part_amb[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float part_diff[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float part_spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float part_shine[] = { 50.0f };

	for (int i = 0; i < MAX_PARTICULAS; i++){
		
		v = 0.8f*frand() + 0.2f;
		phi = frand()*M_PI;
		theta = 2.0f*frand()*M_PI;

		particulas[i].surface = new VSResSurfRevLib();
		particulas[i].surface->createSphere(0.25f, 25);
		particulas[i].surface->addTexture(0, "assets/particula.bmp");
		particulas[i].surface->setColor(VSResourceLib::AMBIENT, part_amb);
		particulas[i].surface->setColor(VSResourceLib::DIFFUSE, part_diff);
		particulas[i].surface->setColor(VSResourceLib::SPECULAR, part_spec);
		particulas[i].surface->setColor(VSResourceLib::SHININESS, part_shine);
		

		particulas[i].x = position[0];
		particulas[i].y = position[1];
		particulas[i].z = position[2];
		particulas[i].life = 1.0f;
		particulas[i].fade = 0.005f;
		particulas[i].vx = v * cos(theta) * sin(phi);
		particulas[i].vy = v * cos(phi);
		particulas[i].vz = v * sin(theta) * sin(phi);
		particulas[i].ax = 0.1f; /* simular um pouco de vento */
		particulas[i].ay = -0.15f; /* simular a aceleração da gravidade */
		particulas[i].az = 0.0f;
	}
}

void Particles::render(VSShaderLib shader) {
	vsml->loadIdentity(VSMathLib::MODEL);

	for (int i = 0; i < MAX_PARTICULAS; i++){

		if (particulas[i].life > 0.0f) /* só desenha as que ainda estão vivas */
		{
			vsml->pushMatrix(VSMathLib::MODEL);
			vsml->translate(particulas[i].x, particulas[i].y, particulas[i].z);
			particulas[i].surface->render(shader);
			vsml->popMatrix(VSMathLib::MODEL);
		}
	}
}

void Particles::updateParticles() {
	float h;

	h = 0.125f;
	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		particulas[i].x += (h*particulas[i].vx);
		particulas[i].y -= (h*particulas[i].vy);
		particulas[i].z += (h*particulas[i].vz);
		particulas[i].vx += (h*particulas[i].ax);
		particulas[i].vy += (h*particulas[i].ay);
		particulas[i].vz += (h*particulas[i].az);
		particulas[i].life -= particulas[i].fade;
	}
}

void Particles::resetParticles() {

	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		GLfloat v, theta, phi;

		v = 0.8f*frand() + 0.2f;
		phi = frand()*M_PI;
		theta = 2.0f*frand()*M_PI;

		particulas[i].x = position[0];
		particulas[i].y = position[1];
		particulas[i].z = position[2];
		particulas[i].life = 1.0f;
		particulas[i].fade = 0.005f;
		particulas[i].vx = v * cos(theta) * sin(phi);
		particulas[i].vy = v * cos(phi);
		particulas[i].vz = v * sin(theta) * sin(phi);
		particulas[i].ax = 0.1f; /* simular um pouco de vento */
		particulas[i].ay = -0.15f; /* simular a aceleração da gravidade */
		particulas[i].az = 0.0f;
	}
}