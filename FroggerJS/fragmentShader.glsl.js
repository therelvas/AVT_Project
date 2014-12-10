var fragmentShaderSrc = 

	"precision mediump float;" +

	"struct LightSource {" +
		"bool isEnabled;" +
		"bool isLocal;" +
		"bool isSpot;" +
		"vec4 l_pos;" +
		"vec4 l_spotDir;" +
		"float l_spotCutOff;" +
	"};" +

	"struct Materials {" +
		"vec4 diffuse;" +
		"vec4 ambient;" +
		"vec4 specular;" +
		"vec4 emissive;" +
		"float shininess;" +
		"int texCount;" +
	"};" +

	"struct FogParameters {" + 
		"bool isEnabled;" +
		"float vFogColorR;" +
		"float vFogColorG;" +
		"float vFogColorB;" +
		"float fStart;" +
		"float fEnd;" +
		"float fDensity;" +
    
		"int iEquation;" +
	"};"+
	
	"uniform FogParameters fogParams;" +

	"const int numLights = 8;" +
	"uniform LightSource lights[numLights];" +
	"uniform Materials mat;" +

	"varying vec3 normal;" +
	"varying vec2 texCoord;" +
	"varying vec4 position;" +
	"varying vec4 eye;" +

	"uniform sampler2D texUnit;" +

	"float getFogFactor(FogParameters params, float fFogCoord) {" +
		"float fResult = 0.0;" +
			
		"if(params.iEquation == 0)" +
			"fResult = (params.fEnd-fFogCoord)/(params.fEnd-params.fStart);" +
		"else if(params.iEquation == 1)" +
			"fResult = exp(-params.fDensity*fFogCoord);" +
		"else if(params.iEquation == 2)" +
			"fResult = exp(-pow(params.fDensity*fFogCoord, 2.0));" +

		"fResult = 1.0-clamp(fResult, 0.0, 1.0);" +
    
		"return fResult;" +
	"}" +
	
    "void main(void) {" +

    	//Normalize both input vectors
		"vec3 n = normalize(normal);" +
		"vec3 e = normalize(vec3(-position));" +
	
		"vec4 specular = vec4(0.0);" +
		"vec4 diffuse = vec4(0.0);" +

		"vec3 l = vec3(0.0);" +

		"for (int i = 0; i < numLights; i++) {" +

			"if(!lights[i].isEnabled) {" +
				"continue;" +
			"}" +

			"if (lights[i].isLocal) {" +

				"l = normalize(vec3(lights[i].l_pos - position));" +
			
				//Spotlight
				"if(lights[i].isSpot) {" +
					
					"vec3 s = normalize(vec3(-lights[i].l_spotDir));" +
				
					//Inside the cone?
					"if(dot(s, l) > lights[i].l_spotCutOff) {" +

						"diffuse += max(dot(n, l), 0.0) * mat.diffuse;" +
						
						"if (max(dot(n, l), 0.0) > 0.0) {" +
							"vec3 h = normalize(l + e);" +	
							"specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);" +
						"}" +
					"}" +
				"}" + 
			
				//Point light
				"else {" +

					"diffuse += 0.1 * max(dot(n, l), 0.0) * mat.diffuse;" +

					"if (max(dot(n, l), 0.0) > 0.0) {" +
						"vec3 h = normalize(l + e);" +
						"specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);" +
					"}" +
				"}" +
			"}" +	

			//Directional Light
			"else {" +
				
				"l = normalize(vec3(lights[i].l_pos));" +

				"diffuse += max(dot(n, l), 0.0) * mat.diffuse;" +

				"if(max(dot(n, l), 0.0) > 0.0) {" +
					"vec3 h = normalize(l + e);" +
					"specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);" +
				"}" +
			"}" +
		"}" +

		//Textures
		"vec4 test = vec4(0.0, 0.0, 0.0, 1.0);" +
		"vec4 texel = texture2D(texUnit, vec2(texCoord.s, texCoord.t));" +
		"vec4 color;" +

		"if(texel==test)" +
			"color = max(diffuse + specular, mat.ambient);" +
		"else color = max(diffuse + specular, mat.ambient)*texel;" +
		
		//Add fog
		"if(fogParams.isEnabled&&color.w>0.0){" +
			"vec4 fogColor = vec4(fogParams.vFogColorR, fogParams.vFogColorG, fogParams.vFogColorB, 1.0);" +
			"float fFogCoord = abs(eye.z/eye.w);" +
			"gl_FragColor = mix(color, fogColor, getFogFactor(fogParams, fFogCoord));" +
		"}" +
		"else gl_FragColor = color;" +
	"}";
