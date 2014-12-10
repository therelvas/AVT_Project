function Tree(x, y, z) {

	this.x = x;
	this.y = y;
	this.z = z;

	this.angle = 0.0;
	this.vectorOrientation = [];
	this.auxVector = [];
	this.vector = [];

	this.surface = new Surface();
	this.setupObjects();
}

Tree.prototype.setupObjects = function() {

	this.vectorOrientation[0] = 1.0;
	this.vectorOrientation[1] = 0.0;
	this.vectorOrientation[2] = 0.0;

	this.surface.setColor("ambient", [0.0, 1.0, 0.0, 1.0]);
	this.surface.setColor("diffuse", [0.0, 1.0, 0.0, 1.0]);
	this.surface.setColor("ambient", [0.0, 1.0, 0.0, 1.0]);
	this.surface.setColor("emissive", [0.0, 0.0, 0.0, 1.0]);
	this.surface.setColor("shininess", [0.0, 0.0, 0.0, 1.0]);
}

Tree.prototype.render = function() {

	mat4.identity(mMatrix);

	pushMatrix();

	mat4.translate(mMatrix, [this.x, this.y, this.z]);

	if ((this.angle < 0.99990) && (this.angle > -0.9999)) {
		//GLMatrix 1.3.7 rotate function doesn't work as expected. We need to upgrade lib version in the future.
		mat4.rotate(mMatrix, Math.acos(-this.angle) * (180.0 / 3.14), this.auxVector);
	}

	mat4.scale(mMatrix, [1.0, 10.0, 8.0]);
	this.surface.render();

	popMatrix();
}

Tree.prototype.updateRotation = function() {

	this.vector[0] = frog.x - this.x;
	this.vector[1] = 0.0;
	this.vector[2] = frog.z - this.z;

	vec3.normalize(this.vector);
	vec3.cross(this.vector, this.vectorOrientation, this.auxVector);
	this.angle = vec3.dot(this.vector, this.vectorOrientation);
}