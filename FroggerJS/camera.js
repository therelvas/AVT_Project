function Camera(v) {

	this.view = v;
	this.ortho = 30.0;
}

Camera.prototype.getView = function() {

	return this.view;
}

Camera.prototype.setView = function(v) {

	this.view = v;
}

Camera.prototype.draw = function(camX, camY, camZ, oX, oY, oZ, side) {

	var width = gl.viewportWidth;
	var height = gl.viewportHeight;

	var ratio = 1.0* (width / height);

	//Orthogonal projection
	if(this.view == 1) {

		mat4.identity(pMatrix);

		gl.viewport(0, 0, width, height);

		if(width > height) {
			mat4.ortho(-this.ortho * ratio, this.ortho * ratio, -this.ortho, this.ortho, -this.ortho, this.ortho + 1.0, pMatrix);
		}
		else {
			mat4.ortho(-this.ortho, this.ortho, -this.ortho * (1.0 / ratio), this.ortho * (1.0 / ratio), -this.ortho, this.ortho + 1.0, pMatrix)
		}

		mat4.identity(vMatrix);
		mat4.identity(mMatrix);

		mat4.lookAt([15.5, this.ortho, 50.0], [15.5 , 0.0, 50.0], [1.0, 0.0, 0.0], vMatrix);
	}

	//Perspective projection
	else if (this.view == 2) {

		mat4.identity(pMatrix);

		gl.viewport(0, 0, width, height);
		mat4.perspective(60.0, ratio, 0.1, 100.0, pMatrix);

        mat4.identity(vMatrix);
        mat4.identity(mMatrix);

        mat4.lookAt([15.5, 55.0, 50.0], [15.5, 0.0, 50.0], [1.0, 0.0, 0.0], vMatrix);
	}

	//Chase cam
	else if (this.view == 3) {

		mat4.identity(pMatrix);

		gl.viewport(0, 0, width, height);
		mat4.perspective(60.0, ratio, 0.1, 100.0, pMatrix);

		mat4.identity(vMatrix);
		mat4.identity(mMatrix);
		
		mat4.lookAt([oX - 10.0, oY + 6.0, oZ], [oX - camX, oY - camY, oZ - camZ], [0.0, 1.0, 0.0], vMatrix);
	}

	//Stereoscopic cam
	else if (this.view == 4) {

		//Left
		if(side == "left") {
			mat4.identity(pMatrix);

			gl.viewport(0, 0, width/2, height);	
			mat4.perspective(60.0, ratio, 0.1, 100.0, pMatrix);

			mat4.identity(vMatrix);
			mat4.identity(mMatrix);
		
			mat4.lookAt([oX - 10.0, oY + 6.0, oZ - 0.025], [oX - camX, oY - camY, oZ - camZ], [0.0, 1.0, 0.0], vMatrix);
		}
		//Right
		else {
			mat4.identity(pMatrix);

			gl.viewport(width/2, 0, width/2, height);	
			mat4.perspective(60.0, ratio, 0.1, 100.0, pMatrix);

			mat4.identity(vMatrix);
			mat4.identity(mMatrix);

			mat4.lookAt([oX - 10.0, oY + 6.0, oZ + 0.025], [oX - camX, oY - camY, oZ - camZ], [0.0, 1.0, 0.0], vMatrix);
		}
	}
}