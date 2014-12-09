function Camera(w, h, v) {

	this.view = v;
	this.width = w;
	this.height = h;
	this.ortho = 30.0;
	this.ratio = 1.0 * (w / h);	
}

Camera.prototype.getView = function() {

	return this.view;
}

Camera.prototype.setView = function(v) {

	this.view = v;
}

Camera.prototype.draw = function(oX, oY, oZ, camX, camY, camZ) {

	//Orthogonal projection
	if(this.view == 1) {

		mat4.identity(pMatrix);

		if(this.width > this.height) {
			mat4.ortho(-this.ortho * this.ratio, this.ortho * this.ratio, -this.ortho, this.ortho, -this.ortho, this.ortho + 1.0, pMatrix);
		}
		else {
			mat4.ortho(-this.ortho, this.ortho, -this.ortho * (1.0 / this.ratio), this.ortho * (1.0 / ratio), -this.ortho, this.ortho + 1.0, pMatrix)
		}

		mat4.identity(vMatrix);
		mat4.identity(mMatrix);

		mat4.lookAt([15.5, this.ortho, 50.0], [15.5 , 0.0, 50.0], [1.0, 0.0, 0.0], vMatrix);
	}

	//Perspective projection
	else if (this.view == 2) {

		mat4.identity(pMatrix);
		mat4.perspective(60.0, this.ratio, 0.1, 1000.0, pMatrix);

        mat4.identity(vMatrix);
        mat4.identity(mMatrix);

        mat4.lookAt([15.5, 55.0, 50.0], [15.5, 0.0, 50.0], [1.0, 0.0, 0.0], vMatrix);
	}

	//Chase cam
	else if (this.view == 3) {

		mat4.identity(pMatrix);
		mat4.perspective(60.0, this.ratio, 0.1, 1000.0, pMatrix);

		mat4.identity(vMatrix);
		mat4.identity(mMatrix);
		
		mat4.lookAt([oX - 10.0, oY + 6.0, oZ], [oX - camX, oY - camY, oZ - camZ], [0.0, 1.0, 0.0], vMatrix);
	}
}