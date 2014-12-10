function RiverMargin(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.light = new Cube();
	this.setupObjects();
}

RiverMargin.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.0215, 0.1745, 0.0215, 1.0]);
	this.cube.setColor("diffuse", [0.07568, 0.61424, 0.07568, 1.0]);
	this.cube.setColor("specular", [0.633, 0.727811, 0.633, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);

	this.light.setColor("ambient", [0.19225, 0.19225, 0.19225, 1.0 ]);
	this.light.setColor("diffuse", [0.50754, 0.50754, 0.50754, 1.0]);
	this.light.setColor("specular", [.508273, 0.508273, 0.508273, 1.0]);
	this.light.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.light.setColor("shininess", 51.2);
}

RiverMargin.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [4.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);

	popMatrix();
	
	pushMatrix();
	mat4.translate(mMatrix, [15, 3.0, 16.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();
	
	pushMatrix();
	mat4.translate(mMatrix, [13.5, 6.0, 16.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [15, 3.0, 56.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();
	
	pushMatrix();
	mat4.translate(mMatrix, [13.5, 6.0, 56.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [15.0, 3.0, 96.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();
	
	pushMatrix();
	mat4.translate(mMatrix, [13.5, 6.0, 96.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	popMatrix();
}