function Cube() {
      
      this.materialAmbient = [1.0,1.0,1.0,1.0];
      this.materialDiffuse = [1.0,1.0,1.0,1.0];
      this.materialSpecular = [1.0,1.0,1.0,1.0];
      this.materialEmissive = [1.0,1.0,1.0,1.0];
      this.materialShininess = 1.0;

      this.setupObjects();
}

Cube.prototype.setupObjects = function() {

      this.cubeVertexPositionBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeVertexPositionBuffer);
      
      var vertices = [
           -0.5,  0.5,  0.5, 1.0,
           -0.5, -0.5,  0.5, 1.0,
            0.5, -0.5,  0.5, 1.0,
            0.5,  0.5,  0.5, 1.0,

            0.5,  0.5, -0.5, 1.0,
            0.5, -0.5, -0.5, 1.0,
           -0.5, -0.5, -0.5, 1.0,
           -0.5,  0.5, -0.5, 1.0,

            0.5,  0.5,  0.5, 1.0,
            0.5, -0.5,  0.5, 1.0,
            0.5, -0.5, -0.5, 1.0,
            0.5,  0.5, -0.5, 1.0,

           -0.5,  0.5, -0.5, 1.0,
           -0.5,  0.5,  0.5, 1.0,
            0.5,  0.5,  0.5, 1.0,
            0.5,  0.5, -0.5, 1.0,

           -0.5,  0.5, -0.5, 1.0,
           -0.5, -0.5, -0.5, 1.0,
           -0.5, -0.5,  0.5, 1.0,
           -0.5,  0.5,  0.5, 1.0,

           -0.5, -0.5,  0.5, 1.0,
           -0.5, -0.5, -0.5, 1.0,
            0.5, -0.5, -0.5, 1.0,
            0.5, -0.5,  0.5, 1.0
      ];

      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
      this.cubeVertexPositionBuffer.itemSize = 4;
      this.cubeVertexPositionBuffer.numItems = 24;

      //Cube Normals
      this.cubeNormalBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeNormalBuffer);

      var normals = [
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,

            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,
            0.0, 0.0, -1.0,

            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,
            1.0, 0.0, 0.0,

            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 0.0,

           -1.0, 0.0, 0.0,
           -1.0, 0.0, 0.0,
           -1.0, 0.0, 0.0,
           -1.0, 0.0, 0.0,

            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0,
            0.0, -1.0, 0.0
      ];

      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
      this.cubeNormalBuffer.itemSize = 3;
      this.cubeNormalBuffer.numItems = 24;

      this.cubeVertexTextureCoordBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeVertexTextureCoordBuffer);
      
      var textureCoords = [
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
      ];
      
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
      this.cubeVertexTextureCoordBuffer.itemSize = 2;
      this.cubeVertexTextureCoordBuffer.numItems = 24;

      this.cubeVertexIndexBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.cubeVertexIndexBuffer);

      var cubeVertexIndices = [
            0, 1, 2,      0, 2, 3,    // Front face
            4, 5, 6,      4, 6, 7,    // Back face
            8, 9, 10,     8, 10, 11,  // Top face
            12, 13, 14,   12, 14, 15, // Bottom face
            16, 17, 18,   16, 18, 19, // Right face
            20, 21, 22,   20, 22, 23  // Left face
      ];

      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
      this.cubeVertexIndexBuffer.itemSize = 1;
      this.cubeVertexIndexBuffer.numItems = 36;
}

Cube.prototype.setMaterial = function(shaderProgram) {

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

Cube.prototype.setColor = function(materialType, colorVec) {

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

Cube.prototype.render = function() {

      this.setMaterial(shaderProgram);

      //Vertex Position
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeVertexPositionBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, this.cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Normals
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeNormalBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, this.cubeNormalBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Tex Coordinates
      gl.bindBuffer(gl.ARRAY_BUFFER, this.cubeVertexTextureCoordBuffer);
      gl.vertexAttribPointer(shaderProgram.texCoordinatesAttribute, this.cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
        
      //Face Index
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.cubeVertexIndexBuffer);
      sendMatricesToGL();
      gl.drawElements(gl.TRIANGLES, this.cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
}