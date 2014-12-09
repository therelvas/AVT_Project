function Obstacles(frog) {
	
	this.frog = frog;
	this.level = 1;

	this.startingPosCarX = [];
	this.startingPosWoodX = [];
	this.startingPosTurtleX = [];

	this.enemies = [];

	this.setStartingPositions();
	this.generateEnemies();
}

Obstacles.prototype.setLevel = function(level) {

	this.level = level;
}

Obstacles.prototype.setStartingPositions = function () {

	this.startingPosCarX[0] = 6.0;
	this.startingPosCarX[1] = 9.0;
	this.startingPosCarX[2] = 12.0;

	this.startingPosWoodX[0] = 20.0;
	this.startingPosWoodX[1] = 26.0;
	this.startingPosWoodX[2] = 26.0;

	this.startingPosTurtleX[0] = 23.0;
}

Obstacles.prototype.generateEnemies = function() {

	var size = this.enemies.length;

	while (size < 20) {

		var type = Math.floor(Math.random() * 25);
		var pos = Math.floor(Math.random() * 3);

		//Car
		if (type < 10) {
			this.enemies.push(new Car(this.startingPosCarX[pos], 0.0, 0.0));
		} 
		else if (type >= 10 && type <= 15) {
			this.enemies.push(new Turtle(this.startingPosTurtleX[0], 0.0, 100.0));
		} 
		else if (type > 15) {
			//this.enemies.push(new Wood(startingPosWoodX[pos], -1.0, 0.0));
		}
		size = this.enemies.length;
	}
}

Obstacles.prototype.updatePosition = function() {

	var size = this.enemies.length;
	var move;

	
	for(var i = 0; i < size; i++) {
		move = Math.floor(Math.random() * 150);
		//this.enemies[i].collide(this.frog);

		if (this.enemies[i].isInitialPos() && move == 1) {
			this.enemies[i].move(this.level);
		}
		else if (!this.enemies[i].isInitialPos()) {
			this.enemies[i].move(this.level);
		}
	}
	//this.frog.collide(this.frog);
}

Obstacles.prototype.render = function() {

	var size = this.enemies.length;
	
	for (var i = 0; i < size; i++) {
		if (!this.enemies[i].isInitialPos()) {
			this.enemies[i].render(shaderProgram);
		}	
	}
}

Obstacles.prototype.destroyObstacles = function() {

	var size = this.enemies.length;

	for (var i = 0; i < size; i++) {
		var actual = this.enemies[i].z;
		if (actual > 100.0 || actual < 0.0) {
			this.enemies[i].resetPosition();
		}
	}
}