#version 330 core

in vec2 v_LocalPosition;
in vec4 v_Color;
in vec2 v_Fade;

out vec4 FragColor;

void main() {
    float alpha = 1.0;

    if (v_Fade.y > 0) {
        float edge = 0.5;

        float dx = abs(v_LocalPosition.x);
        float widthFade = 1.0 - smoothstep(
            edge - clamp(v_Fade.x, 0.002, edge),
            edge,
            dx
        );

        float dy = abs(v_LocalPosition.y);
        float heightFade = 1.0 - smoothstep(
            edge - clamp(v_Fade.y, 0.002, edge),
            edge,
            dy
        );

        alpha = widthFade * heightFade;
    }

    FragColor = vec4(v_Color.rgb, v_Color.a * alpha);
}