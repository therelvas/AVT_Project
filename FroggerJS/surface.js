function Surface() {

	this.materialAmbient  = [1.0,1.0,1.0,1.0];
    this.materialDiffuse  = [1.0,1.0,1.0,1.0];
    this.materialSpecular = [1.0,1.0,1.0,1.0];
    this.materialEmissive = [1.0,1.0,1.0,1.0];
    this.materialShininess = 1.0;

    this.setupObjects();
}

Surface.prototype.setupObjects = function() {

	  this.surfaceVertexPositionBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceVertexPositionBuffer);
      
      var vertices = [

      	0.0,  0.5, -0.5, 1.0,
		0.0, -0.5, -0.5, 1.0,
		0.0, -0.5,  0.5, 1.0,
		0.0,  0.5,  0.5, 1.0,
      ];

      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
      this.surfaceVertexPositionBuffer.itemSize = 4;
      this.surfaceVertexPositionBuffer.numItems = 4;

      //Surface Normals
      this.surfaceNormalBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceNormalBuffer);

      var normals = [
        
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
      ];

      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
      this.surfaceNormalBuffer.itemSize = 3;
      this.surfaceNormalBuffer.numItems = 4;

      this.surfaceVertexTextureCoordBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceVertexTextureCoordBuffer);
      
      var textureCoords = [

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
      ];
      
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
      this.surfaceVertexTextureCoordBuffer.itemSize = 2;
      this.surfaceVertexTextureCoordBuffer.numItems = 24;

      this.surfaceVertexIndexBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.surfaceVertexIndexBuffer);

      var surfaceVertexIndices = [
            0, 1, 2, 0, 2, 3,
      ];

      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(surfaceVertexIndices), gl.STATIC_DRAW);
      this.surfaceVertexIndexBuffer.itemSize = 1;
      this.surfaceVertexIndexBuffer.numItems = 6;
}

Surface.prototype.setMaterial = function() {

      var loc = gl.getUniformLocation(shaderProgram, "mat.ambient");
      gl.uniform4fv(loc, this.materialAmbient);
      loc = gl.getUniformLocation(shaderProgram, "mat.diffuse");
      gl.uniform4fv(loc, this.materialDiffuse);
      loc = gl.getUniformLocation(shaderProgram, "mat.specular");
      gl.uniform4fv(loc, this.materialSpecular);
      loc = gl.getUniformLocation(shaderProgram, "mat.emissive");
      gl.uniform4fv(loc, this.materialEmissive);
      loc = gl.getUniformLocation(shaderProgram, "mat.shininess");
      gl.uniform1f(loc, this.materialShininess);
}

Surface.prototype.setColor = function(materialType, colorVec) {

      if(materialType == "ambient") {
            this.materialAmbient = colorVec;
      } else if (materialType == "diffuse") {
            this.materialDiffuse = colorVec;
      } else if (materialType == "specular") {
            this.materialSpecular = colorVec;
      } else if (materialType == "emissive") {
            this.materialEmissive = colorVec;
      } else if (materialType == "shininess") {
            this.materialShininess = colorVec
      }
}

Surface.prototype.render = function() {

      this.setMaterial(shaderProgram);

      //Vertex Position
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceVertexPositionBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, this.surfaceVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Normals
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceNormalBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, this.surfaceNormalBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Tex Coordinates
      gl.bindBuffer(gl.ARRAY_BUFFER, this.surfaceVertexTextureCoordBuffer);
      gl.vertexAttribPointer(shaderProgram.texCoordinatesAttribute, this.surfaceVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
        
      //Face Index
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.surfaceVertexIndexBuffer);
      sendMatricesToGL();
      gl.drawElements(gl.TRIANGLES, this.surfaceVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
}
