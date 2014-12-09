function Light() {
	
	this.lights = [];

	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
	this.lights.push({ isEnabled: false, isLocal: false, isSpot: false, l_pos: [0,0,0,1], l_spotDir: [0,0,0,1], l_spotCutOff: 0.0})
}

Light.prototype.addLight = function(lightType, pos, spotDir, spotCutOff, index) {

	if(index < 8) {

		if(lightType == "directional") {

			this.lights[index].isEnabled = true;
			this.lights[index].isLocal = false;
			this.lights[index].isSpot = false;
			this.lights[index].l_pos = pos;

		} else if(lightType == "point") {

			this.lights[index].isEnabled = false;
			this.lights[index].isLocal = true;
			this.lights[index].isSpot = false;
			this.lights[index].l_pos = pos;

		} else if(lightType == "spot") {

			this.lights[index].isEnabled = false;
			this.lights[index].isLocal = true;
			this.lights[index].isSpot = true;
			this.lights[index].l_pos = pos;
			this.lights[index].l_spotDir = spotDir;
			this.lights[index].l_spotCutOff = spotCutOff;
		}
	}
}

Light.prototype.draw = function(shaderProgram) {

	for(var i = 0; i < 8; i++) {

		//Enabled bool
		var loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].isEnabled", i));
		gl.uniform1i(loc, this.lights[i].isEnabled);

		//Local bool
		loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].isLocal", i));
		gl.uniform1i(loc, this.lights[i].isLocal);

		//Spot bool
		loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].isSpot", i));
		gl.uniform1i(loc, this.lights[i].isSpot);

		if(this.lights[i].isLocal) {

			//Light position
			loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].l_pos", i));
			gl.uniform4fv(loc, multMatrixPoint(this.lights[i].l_pos, vMatrix));

			if(this.lights[i].isSpot) {

				//Spotlight direction
				loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].l_spotDir", i));
				gl.uniform4fv(loc, multMatrixPoint(this.lights[i].l_spotDir, vMatrix));

				//Spotlight cutoff
				loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].l_spotCutOff", i));
				gl.uniform1f(loc, this.lights[i].l_spotCutOff);
			}
		}
		else {

			//Light position
			loc = gl.getUniformLocation(shaderProgram, String.format("lights[{0}].l_pos", i));
			gl.uniform4fv(loc, multMatrixPoint(this.lights[i].l_pos, vMatrix));
		}
	}
}

Light.prototype.switchLight = function(index) {

	if (this.lights[index].isEnabled) {
		this.lights[index].isEnabled = false;
	}
	else {
		this.lights[index].isEnabled = true;
	}
}