function Particles( x, y, z){

	this.particulas = [];
	
	for(var i = 0; i < 400; i++){//MAX_PARTICLES=400
		this.particulas.push({ sphere: new Sphere(0.25), x: x, y: y, z: z, life: 1, fade: 0.005, vx: 0.0, vy: 0.0, vz: 0.0, ax: 0.1, ay: -0.15, az: 0.0})
	}
	this.setupObjects();
}

Particles.prototype.setupObjects = function(){
	
	var v, theta, phi;

	for (var i = 0; i < 400; i++){ //MAX_PARTICLES=400
		
		v = 0.8*Math.random() + 0.2;
		phi = Math.random()*3.14159265;
		theta = 2.0*Math.random()*3.14159265;

		//this.particulas[i].surface->addTexture(0, "assets/particula.bmp");
		this.particulas[i].sphere.setColor("ambient", [1.0, 1.0, 0.0, 1.0]);
		this.particulas[i].sphere.setColor("diffuse", [1.0, 1.0, 0.0, 1.0]);
		this.particulas[i].sphere.setColor("specular", [1.0, 1.0, 0.0, 1.0]);
		this.particulas[i].sphere.setColor("shininess", 50.0);

		this.particulas[i].vx = v * Math.cos(theta) * Math.sin(phi);
		this.particulas[i].vy = v * Math.cos(phi);
		this.particulas[i].vz = v * Math.sin(theta) * Math.sin(phi);
	}
}

Particles.prototype.render = function(shaderProgram) {
	
	mat4.identity(mMatrix);


	for (var i = 0; i < 400; i++){
		pushMatrix();
		if (this.particulas[i].life > 0.0) /* só desenha as que ainda estão vivas */
		{
			mat4.translate(mMatrix, [this.particulas[i].x, this.particulas[i].y, this.particulas[i].z]);
			this.particulas[i].sphere.render(shaderProgram);
			
		}
		popMatrix();
	}
}

Particles.prototype.updateParticles = function(){
	var h;

	h = 0.125;
	for (var i = 0; i < 400; i++)
	{
		this.particulas[i].x += (h*this.particulas[i].vx);
		this.particulas[i].y -= (h*this.particulas[i].vy);
		this.particulas[i].z += (h*this.particulas[i].vz);
		this.particulas[i].vx += (h*this.particulas[i].ax);
		this.particulas[i].vy += (h*this.particulas[i].ay);
		this.particulas[i].vz += (h*this.particulas[i].az);
		this.particulas[i].life -= this.particulas[i].fade;
	}
}

Particles.prototype.resetParticles = function(){

	for (var i = 0; i < 400; i++)
	{
		var v, theta, phi;

		v = 0.8*Math.random() + 0.2;
		phi = Math.random()*3.14159265;
		theta = 2.0*Math.random()*3.14159265;

		this.particulas[i].x = 35.0;
		this.particulas[i].y = 5.0;
		this.particulas[i].z = 50.0;
		this.particulas[i].life = 1.0;
		this.particulas[i].fade = 0.005;
		this.particulas[i].vx = v * Math.cos(theta) * Math.sin(phi);
		this.particulas[i].vy = v * Math.cos(phi);
		this.particulas[i].vz = v * Math.sin(theta) * Math.sin(phi);
		this.particulas[i].ax = 0.1; /* simular um pouco de vento */
		this.particulas[i].ay = -0.15; /* simular a aceleração da gravidade */
		this.particulas[i].az = 0.0;
	}
}
