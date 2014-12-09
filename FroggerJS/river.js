function River(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.setupObjects();
}

River.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.0, 0.1, 0.06, 1.0]);
	this.cube.setColor("diffuse", [0.0, 0.50980392, 0.50980392, 1.0]);
	this.cube.setColor("specular", [0.50196078, 0.50196078, 0.50196078, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);
}

River.prototype.render = function(shaderProgram) {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [10.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
}