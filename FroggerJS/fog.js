function Fog() {
	
	this.fogParams = { isEnabled: false, fDensity: 0.02, vFogColorR: 0.7, vFogColorG: 0.7, vFogColorB: 0.7, fStart: 10.0, fEnd: 75.0, iEquation: 2};
}

Fog.prototype.draw = function() {

		//Enabled bool
		var loc = gl.getUniformLocation(shaderProgram, "fogParams.isEnabled");
		gl.uniform1i(loc, this.fogParams.isEnabled);

		//Fog density
		loc = gl.getUniformLocation(shaderProgram, "fogParams.fDensity");
		gl.uniform1f(loc, this.fogParams.fDensity);

		//Red color
		loc = gl.getUniformLocation(shaderProgram, "fogParams.vFogColorR");
		gl.uniform1f(loc, this.fogParams.vFogColorR);

		//Green color
		loc = gl.getUniformLocation(shaderProgram, "fogParams.vFogColorG");
		gl.uniform1f(loc, this.fogParams.vFogColorG);
		
		//Blue color
		loc = gl.getUniformLocation(shaderProgram, "fogParams.vFogColorB");
		gl.uniform1f(loc, this.fogParams.vFogColorB);
		
		//
		loc = gl.getUniformLocation(shaderProgram, "fogParams.fStart");
		gl.uniform1f(loc, this.fogParams.fStart);
		
		//
		loc = gl.getUniformLocation(shaderProgram, "fogParams.fEnd");
		gl.uniform1f(loc, this.fogParams.fEnd);
		
		//
		loc = gl.getUniformLocation(shaderProgram, "fogParams.iEquation");
		gl.uniform1i(loc, this.fogParams.iEquation);
}

Fog.prototype.switchFog = function() {

	if (this.fogParams.isEnabled) {
		this.fogParams.isEnabled = false;
	}
	else {
		this.fogParams.isEnabled = true;
	}
}