#version 330 core

in vec2 v_UV;

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;
uniform sampler2D Shadow;
out vec4  Color;
uniform vec3 CameraPosition;
uniform vec3 LightDirection;
uniform vec3 LightColor;

uniform float ShadowBias;
uniform float ShadowSamples;
uniform float ShadowSampleSpread;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;
uniform mat4  LightProjection;

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);


void main(void)
{

	vec4  material = texture(Material, v_UV).rgba;
	vec3  normal = texture(Normal, v_UV).rgb;
	float depth = texture(Depth, v_UV).r;
	
	vec2 xy = v_UV * 2.0 -1.0;
	vec4 wPosition = vec4(xy, depth * 2.0 -1.0, 1.0) * InverseViewProjection;
	vec3 position = vec3(wPosition/wPosition.w);

	vec3 diffuse = material.rgb;
	float spec = texture(Normal, v_UV).a;
	vec3 n = normalize(normal);
	
	float coeffSpec = 100.0;
    vec3 l =  -LightDirection;
	vec3 v = position - CameraPosition;
	vec3 h = normalize(l-v);
	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);
	vec3 color = LightColor * LightIntensity * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * coeffSpec));


        vec4 wlightSpacePosition = LightProjection * vec4(position, 1.0);
        vec3 lightSpacePosition = vec3(wlightSpacePosition/wlightSpacePosition.w);
        if(lightSpacePosition.x > 0.0 && lightSpacePosition.x < 1.0 &&
                lightSpacePosition.y > 0.0 && lightSpacePosition.y < 1.0 &&
                wlightSpacePosition.w  >0.0)
        {

                float visibility = 1.0; 
                for (int i=0;i<16;i++){
                  if ( texture2D( Shadow, lightSpacePosition.xy + poissonDisk[i]/700.0 ).z  <  lightSpacePosition.z-ShadowBias ){
                    visibility-=0.2;
                  }
                }
                Color = vec4(color * visibility, 1.0); 

        }

        else Color = vec4(color, 1.0);
}



/*


in vec2 v_UV;

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;
uniform sampler2D Shadow;

uniform vec3 CameraPosition;
uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;
uniform mat4  LightProjection;
uniform float ShadowBias;
uniform float ShadowSamples;
uniform float ShadowSampleSpread;

out vec4  Color;

vec3 directionalLight(in vec3 n, in vec3 v, in vec3 diffuseColor, in vec3 specularColor, in float specularPower)
{
    vec3 l = normalize(-LightDirection);
    float ndotl = max(dot(n, l), 0.0);
    vec3 h = normalize(l+v);
    float ndoth = max(dot(n, h), 0.0);
    return LightColor * LightIntensity * (diffuseColor * ndotl + specularColor * pow(ndoth, specularPower));;
}

void main(void)
{
    vec4 colorBuffer = texture(Material, v_UV).rgba;
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
    Color = vec4(directionalLight(n, v, diffuseColor, specularColor, specularPower), 1.0);
}

*/