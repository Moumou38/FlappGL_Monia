#version 330 core

in vec2 v_UV;

uniform sampler2D Depth;
uniform mat4 ScreenToView;
uniform vec3 Focus;

out vec4 Color;

void main(void)
{
    float FocusPlane = Focus.x;
    float Near = Focus.y;
    float Far = Focus.z;

    float depth = texture(Depth, v_UV).r;
    vec2  xy = v_UV * 2.0 -1.0;
    vec4  wViewPos =  ScreenToView * vec4(xy, depth * 2.0 -1.0, 1.0);
    vec3  viewPos = vec3(wViewPos/wViewPos.w);
    float viewDepth = -viewPos.z;

    if( viewDepth < Focus.x )
        Color = vec4( clamp( abs( (viewDepth - Focus.x) / Focus.y ), 0.0, 1.0), 0.0, 0.0, 1.0 );
    else
        Color = vec4( clamp( abs( (viewDepth - Focus.x) / Focus.z ), 0.0, 1.0), 0.0, 0.0, 1.0 );
}

