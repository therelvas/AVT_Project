function Frog(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.iX = x;
	this.iY = y;
	this.iZ = z;

	this.eye = new Sphere(0.2);
	this.frogBody = new Sphere(0.5);

	this.gamePoints = 0;
	this.lives = 0;

	this.setupObjects();
}

Frog.prototype.setupObjects = function() {

	//Body
	this.frogBody.setColor("ambient", [ 0.05, 0.05, 0.0, 1.0]);
	this.frogBody.setColor("diffuse", [0.1, 0.55, 0.1, 1.0]);
	this.frogBody.setColor("specular", [0.35, 0.65, 0.45, 1.0]);
	this.frogBody.setColor("emissive", [0.727811, 0.626959, 0.626959, 1.0]);
	this.frogBody.setColor("shininess", 0.25);

	//Eyes
	this.eye.setColor("ambient", [1.0, 1.0, 1.0, 1.0]);
	this.eye.setColor("diffuse", [1.0, 1.0, 1.0, 1.0]);
	this.eye.setColor("specular", [1.0, 1.0, 1.0, 1.0]);
	this.eye.setColor("emissive", [1.0, 1.0, 1.0, 1.0]);
	this.eye.setColor("shininess", 0);
}

Frog.prototype.render = function() {

	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.5, this.y + 0.5, this.z]);
	this.frogBody.render(shaderProgram);

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.8, this.y + 0.8, this.z + 0.2]);
	this.eye.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.8, this.y + 0.8, this.z - 0.2]);
	this.eye.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x - 0.05, this.y, this.z]);
	mat4.scale(mMatrix, [1.0, 1.0, 2.0]);
	this.frogBody.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z + 0.5]);
	this.frogBody.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z - 0.5]);
	this.frogBody.render();

	popMatrix();	
}

Frog.prototype.renderReflection = function() {

	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.5, -(this.y + 1.5), this.z]);
	this.frogBody.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.8, -(this.y + 1.8), this.z + 0.2]);
	this.eye.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x + 0.8, -(this.y + 1.8), this.z - 0.2]);
	this.eye.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, -[this.y + 1.0], this.z]);
	mat4.scale(mMatrix, [1.0, 1.0, 2.0]);
	this.frogBody.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, -(this.y + 1.0), this.z + 0.5]);
	this.frogBody.render();

	popMatrix();

	pushMatrix();

	mat4.translate(mMatrix, [this.x, -(this.y + 1.0), this.z - 0.5]);
	this.frogBody.render();

	popMatrix();	
}

Frog.prototype.move = function(x, y, z, speed){

	if (!(this.x + x*speed <= 32 && this.x + x*speed >= 0))
		return;
	if (!(this.z + z*speed <= 100 && this.z + z*speed >= 0))
		return;

	this.x += x * speed;
	this.y += y * speed;
	this.z += z * speed;
}

Frog.prototype.getBoundingBox = function(){

	var boundingBox = [[],[]];

	boundingBox[0][0] = this.x +1.2;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = this.z - 1;

	boundingBox[1][0] = this.x - 1.2;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = this.z + 1;

	return boundingBox;
}

Frog.prototype.resetLifes = function(){
	this.lives = 5;
	this.gamePoints = 0;
}

Frog.prototype.loseLife = function(){
	this.lives--;
}

Frog.prototype.getPoints = function(){
	return this.gamePoints;
}

Frog.prototype.getLives = function(){
	return this.lives;
}

Frog.prototype.isInitialPos = function() {

	if(this.x == this.iX && this.y == this.iY && this.z == this.iZ) {
		return true;
	} else {
		return false;
	}
}

Frog.prototype.resetPosition = function() {

	this.x = this.iX;
	this.y = this.iY;
	this.z = this.iZ;
}

Frog.prototype.collide = function() {
	if (this.x >= 31){
		this.gamePoints += 10;
		this.resetPosition();
	}
}