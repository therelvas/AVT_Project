function Road(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.setupObjects();
}

Road.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.05375, 0.05, 0.06625, 1.0]);
	this.cube.setColor("diffuse", [0.18275, 0.17, 0.22525, 1.0]);
	this.cube.setColor("specular", [0.332741, 0.328634, 0.346435, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);
}

Road.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [10.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
}