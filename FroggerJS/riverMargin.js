function RiverMargin(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.setupObjects();
}

RiverMargin.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.0215, 0.1745, 0.0215, 1.0]);
	this.cube.setColor("diffuse", [0.07568, 0.61424, 0.07568, 1.0]);
	this.cube.setColor("specular", [0.633, 0.727811, 0.633, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);
}

RiverMargin.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [4.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
}