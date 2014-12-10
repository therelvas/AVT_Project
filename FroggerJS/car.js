function Car(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.iX = x;
	this.iY = y;
	this.iZ = z;

	this.cube = new Cube();
	this.sphere = new Sphere(0.5);
	this.setupObjects();
}

Car.prototype.setupObjects = function() {

	//Body
	this.cube.setColor("ambient", [0.1745, 0.01175, 0.01175, 1.0]);
	this.cube.setColor("diffuse", [0.61424, 0.04136, 0.04136, 1.0]);
	this.cube.setColor("specular", [0.332741, 0.328634, 0.346435, 1.0]);
	this.cube.setColor("emissive", [0.727811, 0.626959, 0.626959, 1.0]);
	this.cube.setColor("shininess", 76.8);

	//Tires
	this.sphere.setColor("ambient", [0.0, 0.0, 0.0, 1.0]);
	this.sphere.setColor("diffuse", [0.0, 0.0, 0.0, 1.0]);
	this.sphere.setColor("specular", [0.0, 0.0, 0.0, 1.0]);
	this.sphere.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.sphere.setColor("shininess", 0);
}

Car.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y + 0.5, this.z]);
	mat4.scale(mMatrix, [2.0, 1.0, 5.0]);
	this.cube.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y + 1.5, this.z]);
	mat4.scale(mMatrix, [2.0, 1.0, 3.0]);
	this.cube.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 1, this.y, this.z - 1.25]);
	mat4.scale(mMatrix, [0.5,1,1]);
	this.sphere.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x - 1, this.y, this.z - 1.25]);
	mat4.scale(mMatrix, [0.5,1,1]);
	this.sphere.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 1, this.y, this.z + 1.25]);
	mat4.scale(mMatrix, [0.5,1,1]);
	this.sphere.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x - 1, this.y, this.z + 1.25]);
	mat4.scale(mMatrix, [0.5,1,1]);
	this.sphere.render(shaderProgram);

	popMatrix();
}

Car.prototype.move = function(speed){

	this.z += 0.2 * speed;
}

Car.prototype.getBoundingBox = function(){

	var boundingBox = [[],[]];

	boundingBox[0][0] = this.x +1.5;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = this.z - 2.5;

	boundingBox[1][0] = this.x - 1.5;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = this.z + 2.5;

	return boundingBox;

}

Car.prototype.isInitialPos = function() {

	if(this.x == this.iX && this.y == this.iY && this.z == this.iZ) {
		return true;
	} else {
		return false;
	}
}

Car.prototype.resetPosition = function() {

	this.x = this.iX;
	this.y = this.iY;
	this.z = this.iZ;
}

Car.prototype.collide = function(frog){
	var frogBoundingBox = frog.getBoundingBox();
	var carBoundingBox = this.getBoundingBox();
	if(frogBoundingBox[0][0] >= carBoundingBox[1][0] && frogBoundingBox[0][0] <= carBoundingBox[0][0]
		&&
		frogBoundingBox[0][2] <= carBoundingBox[1][2] && frogBoundingBox[0][2] >= carBoundingBox[0][2]){
		frog.loseLife()
		frog.resetPosition();
	}else{
		if (frogBoundingBox[1][0] >= carBoundingBox[1][0] && frogBoundingBox[1][0] <= carBoundingBox[0][0] &&
		frogBoundingBox[1][2] <= carBoundingBox[1][2] && frogBoundingBox[1][2] >= carBoundingBox[0][2]){
			frog.loseLife();
			frog.resetPosition();
		}
	}
}