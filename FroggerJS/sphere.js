function Sphere(radius) {

      this.materialAmbient = [1.0,1.0,1.0,1.0];
      this.materialDiffuse = [1.0,1.0,1.0,1.0];
      this.materialSpecular = [1.0,1.0,1.0,1.0];
      this.materialEmissive = [1.0,1.0,1.0,1.0];
      this.materialShininess = 1.0;

      this.setupObjects(radius);
}

Sphere.prototype.setupObjects = function(radius) {

      var latitudeBands = 30;
      var longitudeBands = 30;
      var vertexPositionData = [];
      var normalData = [];
      var textureCoordData = [];
      
      for (var latNumber=0; latNumber <= latitudeBands; latNumber++) {
            var theta = latNumber * Math.PI / latitudeBands;
            var sinTheta = Math.sin(theta);
            var cosTheta = Math.cos(theta);
            for (var longNumber=0; longNumber <= longitudeBands; longNumber++) {
                  var phi = longNumber * 2 * Math.PI / longitudeBands;
                  var sinPhi = Math.sin(phi);
                  var cosPhi = Math.cos(phi);
                  var x = cosPhi * sinTheta;
                  var y = cosTheta;
                  var z = sinPhi * sinTheta;
                  var u = 1 - (longNumber / longitudeBands);
                  var v = 1 - (latNumber / latitudeBands);
                  normalData.push(x);
                  normalData.push(y);
                  normalData.push(z);
                  textureCoordData.push(u);
                  textureCoordData.push(v);
                  vertexPositionData.push(radius * x);
                  vertexPositionData.push(radius * y);
                  vertexPositionData.push(radius * z);
            }
      }
      var indexData = [];
      for (var latNumber=0; latNumber < latitudeBands; latNumber++) {
            for (var longNumber=0; longNumber < longitudeBands; longNumber++) {
                  var first = (latNumber * (longitudeBands + 1)) + longNumber;
                  var second = first + longitudeBands + 1;
                  indexData.push(first);
                  indexData.push(second);
                  indexData.push(first + 1);
                  indexData.push(second);
                  indexData.push(second + 1);
                  indexData.push(first + 1);
            }
      }
        
      this.sphereVertexNormalBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexNormalBuffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normalData), gl.STATIC_DRAW),
      this.sphereVertexNormalBuffer.itemSize = 3;
      this.sphereVertexNormalBuffer.numItems = normalData.length / 3;
     
      this.sphereVertexTextureCoordBuffer = gl.createBuffer(); 
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexTextureCoordBuffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordData), gl.STATIC_DRAW);  
      this.sphereVertexTextureCoordBuffer.itemSize = 2;
      this.sphereVertexTextureCoordBuffer.numItems = textureCoordData.length / 2;
      
      this.sphereVertexPositionBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexPositionBuffer);
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexPositionData), gl.STATIC_DRAW);
      this.sphereVertexPositionBuffer.itemSize = 3;
      this.sphereVertexPositionBuffer.numItems = vertexPositionData.length / 3;
      
      this.sphereVertexIndexBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.sphereVertexIndexBuffer);
      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexData), gl.STATIC_DRAW);
      this.sphereVertexIndexBuffer.itemSize = 1;
      this.sphereVertexIndexBuffer.numItems = indexData.length;
}

Sphere.prototype.setMaterial = function() {

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

Sphere.prototype.setColor = function(materialType, colorVec) {

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

Sphere.prototype.render = function() {

      this.setMaterial();

      //Vertex Position
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexPositionBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, this.sphereVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Normals
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexNormalBuffer);
      gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, this.sphereVertexNormalBuffer.itemSize, gl.FLOAT, false, 0, 0);

      //Tex Coordinates
      gl.bindBuffer(gl.ARRAY_BUFFER, this.sphereVertexTextureCoordBuffer);
      gl.vertexAttribPointer(shaderProgram.texCoordinatesAttribute, this.sphereVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
        
      //Face Index
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.sphereVertexIndexBuffer);
      sendMatricesToGL();
      gl.drawElements(gl.TRIANGLES, this.sphereVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
}