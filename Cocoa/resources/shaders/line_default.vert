#version 330 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec2 a_LocalPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Fade;

uniform mat4x4 u_ViewProjectionMatrix;

out vec2 v_LocalPosition;
out vec4 v_Color;
out float v_Fade;

void main() {
    gl_Position = u_ViewProjectionMatrix * vec4(a_WorldPosition, 1.0);
    v_LocalPosition = a_LocalPosition;
    v_Color = a_Color;
    v_Fade = a_Fade;
}