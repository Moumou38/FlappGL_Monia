#version 330 core

in vec3 v_UV;

uniform samplerCube SkyboxTexture;

out vec4 Color;

void main()
{
    Color = texture(SkyboxTexture, v_UV);
}

/*


uniform sampler2D normal;

in vec3 v_UV;
vec3 vertexNorm;
vec3 lightPos;
uniform float Near;
uniform float Far;

out vec4 finalData[4];

float saturate(float value)
{
	return clamp(value,0.0,1.0);
}

float LinearizeDepth()
{
  float n = Near; // camera z near
  float f = Far; // camera z far
  float z = gl_FragCoord.z;
  return (2.0 * n) / (f + n - z * (f - n)); 
}

float depth() {
    return LinearizeDepth();
}

void main()
{
	vertexNorm = texture(Normal, v_UV).rgb;
    lightPos = vec3(0,9000,0);
	vec3 horizon = vec3(0.70, 0.40, 0.20);
	vec3 zenith = vec3(0.00, 0.44, 0.81);
	vec3 night = vec3(0.0156, 0.1019, 0.1843);
	vec3 N = normalize(vertexNorm);
    vec3 V = normalize(v_UV);
    vec3 L = normalize(lightPos);

    // Compute the proximity of this fragment to the sun.
    float sundot = dot(N, L);

    // Sun and Moon.
    vec3 moon =  0.8f * vec3(pow( max(0.0001, dot(-L, N)), 360.0f )); 
    vec3 light  = 0.8f * vec3(pow( max(0.0001, sundot), 360.0f ));
   	
   	vec3 c1 = night;// - abs(sundot)*horizon;
    vec3 c2 = zenith;// - abs(sundot)*horizon;
    vec3 c3 = horizon;
    float sun2 = (sundot+1)/2;
    vec3 color;
	

   	float atten = 1-abs(L.y);
   	float dist = length(V-L);
   	color = (c1*sun2+ c2*(1-sun2))*(1-atten) + c3*(atten);



    float curve = 0.25f* (2.0f - L.y);
    vec3 sky = color * (1-curve);
    //sky = sky * (1+sundot) + color * -sundot;
    sky *= saturate(L.y+2.0);

	//vec3 sky = c2;

    finalData[0] = vec4(1.f, vertexPos);
    finalData[1] = vec4((sky + moon + light), 1.f);
    finalData[2] = vec4(normalize(vertexNorm),1.f);
    finalData[3] = vec4(0.f,0.f,0.f,0.f);
    gl_FragDepth = depth();
    //finalData[1] = vec4(N, 1.f);
} */
