#version 330

struct LightSource {
	bool isEnabled;
	bool isLocal;
	bool isSpot;
	vec4 l_pos;
	vec4 l_spotDir;
	float l_spotCutOff;
};

struct Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

const int numLights = 8;
uniform LightSource lights[numLights];
uniform Materials mat;

in Data {
	vec3 normal;
	vec2 texCoord;
	vec4 position;
} DataIn;

uniform sampler2D texUnit;
out vec4 colorOut;

void main() {
	
	// normalize both input vectors
	vec3 n = normalize(DataIn.normal);
	vec3 e = normalize(vec3(-DataIn.position));
	
	vec4 specular = vec4(0.0);
	vec4 diffuse = vec4(0.0);

	vec3 l = vec3(0.0);

	for (int i = 0; i < numLights; i++) {

		if(!lights[i].isEnabled)
			continue;

		if (lights[i].isLocal) {

			l = normalize(vec3(lights[i].l_pos - DataIn.position));
			
			//Spotlight
			if(lights[i].isSpot) {	
					
				vec3 s = normalize(vec3(-lights[i].l_spotDir));
				
				//Inside the cone?
				if(dot(s, l) > lights[i].l_spotCutOff) {

					diffuse += max(dot(n, l), 0.0) * mat.diffuse;
						
					if (max(dot(n, l), 0.0) > 0.0) {
						vec3 h = normalize(l + e);	
						specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);
					}
				}
			} 
			
			//Point light
			else {

				diffuse += 0.1 * max(dot(n, l), 0.0) * mat.diffuse;

				if (max(dot(n, l), 0.0) > 0.0) {
					vec3 h = normalize(l + e);	
					specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);
				}
			}
		}	

		//Directional Light
		else {

			l = normalize(vec3(lights[i].l_pos));
			diffuse += max(dot(n, l), 0.0) * mat.diffuse;	

			if(max(dot(n, l), 0.0) > 0.0) {
				vec3 h = normalize(l + e);
				specular += mat.specular * pow(max(dot(h, n), 0.0), mat.shininess);
			}
		}
	}
	vec4 test = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 texel = texture(texUnit, DataIn.texCoord);
	if(texel==test)
		 colorOut = max(diffuse + specular, mat.ambient);
	else colorOut = max(diffuse + specular, mat.ambient)*texel;
}