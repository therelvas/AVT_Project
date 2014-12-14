function RoadMargin(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.cube = new Cube();
	this.light = new Cube();
	this.setupObjects();
}


RoadMargin.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.25, 0.25, 0.25, 1.0]);
	this.cube.setColor("diffuse", [0.55, 0.55, 0.55, 1.0]);
	this.cube.setColor("specular", [0.70, 0.70, 0.70, 1.0]);
	this.cube.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.cube.setColor("shininess", 80.0);
	
	this.light.setColor("ambient", [0.19225, 0.19225, 0.19225, 1.0 ]);
	this.light.setColor("diffuse", [0.50754, 0.50754, 0.50754, 1.0]);
	this.light.setColor("specular", [.508273, 0.508273, 0.508273, 1.0]);
	this.light.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.light.setColor("shininess", 51.2);

}

RoadMargin.prototype.render = function() {

	mat4.identity(mMatrix);

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);
	mat4.scale(mMatrix, [4.0, 1.0, 100.0]);
	this.cube.render(shaderProgram);
	
	popMatrix();

	//Lights 
	/*
	pushMatrix();
	
	mat4.translate(mMatrix, [2.0, 3.0, 4.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();
	
	pushMatrix();
	
	mat4.translate(mMatrix, [3.5, 6.0, 4.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();

	pushMatrix();
	
	mat4.translate(mMatrix, [2.0, 3.0, 36.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();
	
	pushMatrix();
	
	mat4.translate(mMatrix, [3.5, 6.0, 36.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();

	pushMatrix();
	
	mat4.translate(mMatrix, [2.0, 3.0, 76.0]);
	mat4.scale(mMatrix, [1.0, 6.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();
	
	pushMatrix();
	
	mat4.translate(mMatrix, [3.5, 6.0, 76.0]);
	mat4.scale(mMatrix, [4.0, 1.0, 1.0]);
	this.light.render(shaderProgram);
	
	popMatrix();*/
}