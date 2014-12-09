 String.format = function() {
      var s = arguments[0];
      for (var i = 0; i < arguments.length - 1; i++) {       
          var reg = new RegExp("\\{" + i + "\\}", "gm");             
          s = s.replace(reg, arguments[i + 1]);
      }
      return s;
  }

function multMatrixPoint(point, matrix) {

	var res = vec4.create();

	for (var i = 0; i < 4; ++i) {

		res[i] = 0.0;
	
		for (var j = 0; j < 4; j++) {
		
			res[i] += point[j] * matrix[j*4 + i];
		} 
	}

	return res;
}

function computeNormalMatrix3x3(matrix) {

	var mMat3x3 = mat3.create();
	var mNormal3x3 = mat3.create();

	mMat3x3[0] = matrix[0];
	mMat3x3[1] = matrix[1];
	mMat3x3[2] = matrix[2];

	mMat3x3[3] = matrix[4];
	mMat3x3[4] = matrix[5];
	mMat3x3[5] = matrix[6];

	mMat3x3[6] = matrix[8];
	mMat3x3[7] = matrix[9];
	mMat3x3[8] = matrix[10];

	var det;
	var invDet;

	det = mMat3x3[0] * (mMat3x3[4] * mMat3x3[8] - mMat3x3[5] * mMat3x3[7]) +
		  mMat3x3[1] * (mMat3x3[5] * mMat3x3[6] - mMat3x3[8] * mMat3x3[3]) +
		  mMat3x3[2] * (mMat3x3[3] * mMat3x3[7] - mMat3x3[4] * mMat3x3[6]);

	invDet = 1.0/det;

	mNormal3x3[0] = (mMat3x3[4] * mMat3x3[8] - mMat3x3[5] * mMat3x3[7]) * invDet;
	mNormal3x3[1] = (mMat3x3[5] * mMat3x3[6] - mMat3x3[8] * mMat3x3[3]) * invDet;
	mNormal3x3[2] = (mMat3x3[3] * mMat3x3[7] - mMat3x3[4] * mMat3x3[6]) * invDet;
	mNormal3x3[3] = (mMat3x3[2] * mMat3x3[7] - mMat3x3[1] * mMat3x3[8]) * invDet;
	mNormal3x3[4] = (mMat3x3[0] * mMat3x3[8] - mMat3x3[2] * mMat3x3[6]) * invDet;
	mNormal3x3[5] = (mMat3x3[1] * mMat3x3[6] - mMat3x3[7] * mMat3x3[0]) * invDet;
	mNormal3x3[6] = (mMat3x3[1] * mMat3x3[5] - mMat3x3[4] * mMat3x3[2]) * invDet;
	mNormal3x3[7] = (mMat3x3[2] * mMat3x3[3] - mMat3x3[0] * mMat3x3[5]) * invDet;
	mNormal3x3[8] = (mMat3x3[0] * mMat3x3[4] - mMat3x3[3] * mMat3x3[1]) * invDet;

	return mNormal3x3;
}