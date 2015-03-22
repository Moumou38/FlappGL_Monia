#version 330 core

in vec2 v_UV;

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;
uniform sampler2D Shadow;

uniform vec3 CameraPosition;
uniform vec3  LightPosition;
uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;
uniform mat4  LightProjection;
uniform float ShadowBias;

out vec4  Color;

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
	vec3 l =  LightPosition - position;

	vec3 v = position - CameraPosition;

	vec3 h = normalize(l-v);

	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);

	float cosAngleLD = dot(normalize(l), -normalize(LightDirection));

        float spotAngle = radians(20.0);
        float fallOffAngle = radians(10.0);
	
	vec3 color = vec3(0);
	
	if(cosAngleLD > cos(spotAngle)){
		float falloff = 1.0f;
		if(cosAngleLD < cos(fallOffAngle)){
			falloff = pow( (cosAngleLD - cos(spotAngle)) /  (cos(fallOffAngle) - cos(spotAngle)) , 4);
		}
		color =  falloff * LightColor * LightIntensity * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * coeffSpec));
	}

        vec4 wlightSpacePosition = LightProjection * vec4(position, 1.0);
        vec3 lightSpacePosition = vec3(wlightSpacePosition/wlightSpacePosition.w);
        if(lightSpacePosition.x > 0.0 && lightSpacePosition.x < 1.0 &&
                lightSpacePosition.y > 0.0 && lightSpacePosition.y < 1.0 &&
                wlightSpacePosition.w  >0.0)
        {

                float shadowRead = texture(Shadow, vec2(lightSpacePosition.x, lightSpacePosition.y)).r;

                if(lightSpacePosition.z-shadowRead < ShadowBias) //Lighting
                    Color = vec4(color, 1.0);

                else //Shadow
                    Color = vec4(0.0,0.0,0.0,1.0);
        }

        else Color = vec4(color, 1.0);

}
