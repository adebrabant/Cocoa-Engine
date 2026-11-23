#version 330 core

in vec2 v_LocalPosition;
in vec4 v_Color;
in float v_Fade;

out vec4 FragColor;

void main() {
    FragColor = v_Color;
}