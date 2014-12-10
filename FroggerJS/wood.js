function Wood(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.iX = x;
	this.iY = y;
	this.iZ = z;

	this.cube = new Cube();

	this.setupObjects();
}

Wood.prototype.setupObjects = function() {

	this.cube.setColor("ambient", [0.25, 0.148, 0.06475, 1.0]);
	this.cube.setColor("diffuse", [0.4, 0.2368, 0.1036, 1.0]);
	this.cube.setColor("specular", [0.774597, 0.458561, 0.200621, 1.0]);
	this.cube.setColor("emissive", [0.332741, 0.328634, 0.346435, 1.0]);
	this.cube.setColor("shininess", 76.8);
}

Wood.prototype.render = function() {
	
	mat4.identity(mMatrix);
	
	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y - 0.5, this.z]);
	mat4.scale(mMatrix, [1.0, 1.0, 7.0]);
	this.cube.render();

	popMatrix();
}

Wood.prototype.move = function(speed){

	this.z += 0.2 * speed;
}

Wood.prototype.getBoundingBox = function(){

	var boundingBox = [[],[]];

	boundingBox[0][0] = this.x +1;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = this.z - 3.5;

	boundingBox[1][0] = this.x - 1;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = this.z + 3.5;

	return boundingBox;

}

Wood.prototype.isInitialPos = function() {

	if(this.x == this.iX && this.y == this.iY && this.z == this.iZ) {
		return true;
	} else {
		return false;
	}
}

Wood.prototype.resetPosition = function() {

	this.x = this.iX;
	this.y = this.iY;
	this.z = this.iZ;
}

Wood.prototype.collide = function(frog){
	var frogBoundingBox = frog.getBoundingBox();
	var woodBoundingBox = this.getBoundingBox();
	if(frogBoundingBox[0][0] >= woodBoundingBox[1][0] && frogBoundingBox[0][0] <= woodBoundingBox[0][0]
		&&
		frogBoundingBox[0][2] <= woodBoundingBox[1][2] && frogBoundingBox[0][2] >= woodBoundingBox[0][2]){
		frog.loseLife();
		frog.resetPosition();
	}else{
		if (frogBoundingBox[1][0] >= woodBoundingBox[1][0] && frogBoundingBox[1][0] <= woodBoundingBox[0][0] &&
		frogBoundingBox[1][2] <= woodBoundingBox[1][2] && frogBoundingBox[1][2] >= woodBoundingBox[0][2]){
		frog.loseLife();
		frog.resetPosition();
		}
	}
}