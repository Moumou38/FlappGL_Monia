#version 330 core

in vec2 v_UV;
uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;

uniform vec3 CameraPosition;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;

out vec4  Color;

/*

vec3 pointLight( in vec3 p, in vec3 n, in vec3 v, in vec3 diffuseColor, in vec3 specularColor, in float specularPower)
{
	vec3 l = normalize(LightPosition - p);
	float ndotl = max(dot(n, l), 0.0);
	vec3 h = normalize(l+v);
	float ndoth = max(dot(n, h), 0.0);
	float d = distance(LightPosition, p);
	float att = 1.f / (d*d);
	return att * LightColor * LightIntensity * (diffuseColor * ndotl + specularColor * pow(ndoth, specularPower));
}

*/


void main(void)
{

	/*vec4 colorBuffer = texture(Material, v_UV).rgba;
	vec4 normalBuffer = texture(Normal, v_UV).rgba;
	float depth = texture(Depth, v_UV).r;

	vec3 n = normalBuffer.rgb;
	vec3 diffuseColor = colorBuffer.rgb;
	vec3 specularColor = colorBuffer.aaa;
	float specularPower = normalBuffer.a;

	vec2 xy = v_UV * 2.0 -1.0;
	vec4 wP = InverseViewProjection * vec4(xy, depth * 2.0 -1.0, 1.0);
	vec3 p = vec3(wP.xyz / wP.w);
	vec3 v = normalize(-p);

	Color = vec4(pointLight(p, n, v, diffuseColor, specularColor, specularPower), 1.0);*/


	vec4  material = texture(Material, v_UV).rgba;
	vec3  normal = texture(Normal, v_UV).rgb;
	float depth = texture(Depth, v_UV).r;

	vec2 xy = v_UV * 2.0 -1.0;
	vec4 wPosition = vec4(xy, depth * 2.0 -1.0, 1.0) * InverseViewProjection;
	vec3 position = vec3(wPosition/wPosition.w);

	vec3 diffuse = material.rgb;
	float spec = texture(Normal, v_UV).a;
	vec3 n = normalize(normal);

	float coeffSpec = (texture(Normal, v_UV).rgba).a;
	vec3 l =  LightPosition - position;
	vec3 v = position - CameraPosition;

	vec3 h = normalize(l-v);

	float n_dotl = clamp(dot(n, l), 0, 1.0);
	float n_doth = clamp(dot(n, h), 0, 1.0);
	float distanceToLight = distance(LightPosition, position);
	
	float attenuation = clamp(1.0 / (distanceToLight * distanceToLight), 0.0, 1.0);

	vec3 color = LightColor * LightIntensity * attenuation * (diffuse * n_dotl + spec * vec3(1.0, 1.0, 1.0) *  pow(n_doth, spec * coeffSpec));
	Color = vec4(color, 1.0);
}

