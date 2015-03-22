#version 330 core

in vec2 v_UV;

uniform sampler2D Material;

uniform vec3 LightColor;
uniform float LightIntensity;

out vec4  Color;

void main(void)
{
	vec3 color = LightColor * LightIntensity * texture(Material, v_UV).rgb;
	Color = vec4(color, 1.0);
}
