function River(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.setupObjects();
	this.cube.initTexture("river2.png");
}

River.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.0, 0.1, 0.06, 0.5]);
	this.cube.setColor("diffuse", [0.0, 0.50980392, 0.50980392, 0.5]);
	this.cube.setColor("specular", [0.50196078, 0.50196078, 0.50196078, 0.5]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 0.5]);
	this.cube.setColor("shininess", 70.0);
}

River.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [10.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
}
