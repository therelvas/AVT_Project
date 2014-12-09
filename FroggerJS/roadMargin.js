function RoadMargin(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.setupObjects();
}


RoadMargin.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.25, 0.25, 0.25, 1.0]);
	this.cube.setColor("diffuse", [0.55, 0.55, 0.55, 1.0]);
	this.cube.setColor("specular", [0.70, 0.70, 0.70, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);
}

RoadMargin.prototype.render = function() {

	mat4.identity(mMatrix);

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [4.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
}