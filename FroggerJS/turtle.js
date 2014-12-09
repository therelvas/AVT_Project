function Turtle(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.shell = new Sphere(1.0);
	this.head = new Sphere(0.4);
	this.paws = new Sphere(0.3);

	this.setupObjects();
}

Turtle.prototype.setupObjects = function() {

	this.shell.setColor("ambient", [0.25, 0.148, 0.06475, 1.0]);
	this.shell.setColor("diffuse", [0.4, 0.2368, 0.1036, 1.0]);
	this.shell.setColor("specular", [0.332741, 0.328634, 0.346435, 1.0]);
	this.shell.setColor("emissive", [0.774597, 0.458561, 0.200621, 1.0]);
	this.shell.setColor("shininess", 76.8);

	this.head.setColor("ambient", [0.05, 0.05, 0.0, 1.0]);
	this.head.setColor("diffuse", [0.1, 0.55, 0.1, 1.0]);
	this.head.setColor("specular", [0.332741, 0.328634, 0.346435, 1.0]);
	this.head.setColor("emissive", [ 0.35, 0.65, 0.45, 1.0]);
	this.head.setColor("shininess", 0.25);

	this.paws.setColor("ambient", [0.05, 0.05, 0.0, 1.0]);
	this.paws.setColor("diffuse", [0.1, 0.55, 0.1, 1.0]);
	this.paws.setColor("specular", [0.332741, 0.328634, 0.346435, 1.0]);
	this.paws.setColor("emissive", [ 0.35, 0.65, 0.45, 1.0]);
	this.paws.setColor("shininess", 0.25);
}

Turtle.prototype.render = function() {

	mat4.identity(mMatrix);
	
	pushMatrix();
	mat4.translate(mMatrix, [this.x, this.y - 0.5, this.z]);
	mat4.scale(mMatrix, [1.0, 0.4, 1.0]);
	this.shell.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x, this.y - 0.5, this.z - 1]);
	this.head.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x - 0.9, this.y - 0.6, this.z - 0.7]);
	this.paws.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x + 0.9, this.y - 0.6, this.z + 0.7]);
	this.paws.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x - 0.9, this.y - 0.6, this.z + 0.7]);
	this.paws.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x + 0.9, this.y - 0.6, this.z - 0.7]);
	this.paws.render(shaderProgram);
	popMatrix();

	pushMatrix();
	mat4.translate(mMatrix, [this.x, this.y - 0.6, this.z +1]);
	mat4.scale(mMatrix, [0.7, 1, 2.0]);
	this.paws.render(shaderProgram);
	popMatrix();
}

Turtle.prototype.move = function(speed) {

	this.z -= 0.1 * speed;
}

Turtle.prototype.getBoundingBox = function(){

	var boundingBox = [[],[]];
	
	boundingBox[0][0] = this.x + 1.5;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = this.z - 2;

	boundingBox[1][0] = this.x - 1.5;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = this.z + 2;

	return boundingBox;
}

Turtle.prototype.isInitialPos = function() {

	if(this.x == this.iX && this.y == this.iY && this.z == this.iZ) {
		return true;
	} else {
		return false;
	}
}

Turtle.prototype.resetPosition = function() {

	this.x = this.iX;
	this.y = this.iY;
	this.z = this.iZ;
}

/*Turtle.prototype.collide = function(Frog frog){
	var frogBoundingBox = frog.getBoundingBox();
	var turtleBoundingBox = this.getBoundingBox();
	if(frogBoundingBox[0][0] >= turtleBoundingBox[1][0] && frogBoundingBox[0][0] <= turtleBoundingBox[0][0]
		&&
		frogBoundingBox[0][2] <= turtleBoundingBox[1][2] && frogBoundingBox[0][2] >= turtleBoundingBox[0][2]){
		frog.

	();
		frog.resetPosition();
	}else{
		if (frogBoundingBox[1][0] >= turtleBoundingBox[1][0] && frogBoundingBox[1][0] <= turtleBoundingBox[0][0] &&
		frogBoundingBox[1][2] <= turtleBoundingBox[1][2] && frogBoundingBox[1][2] >= turtleBoundingBox[0][2]){
		frog.loseLife();
		frog.resetPosition();
	}
}*/
