#version 330 core

in vec2 v_LocalPosition;
in vec4 v_Color;
in float v_Thickness;
in float v_Fade;

out vec4 FragColor;

void main() {
    float distance = length(v_LocalPosition);
    float outerRadius = 0.5;
    float innerRadius = outerRadius - v_Thickness;
    float alpha = 0.0;

    if (v_Fade <= 0.0) {
        // no fade is set do a hard cut
        if (distance <= innerRadius && distance >= outerRadius) {
            alpha = 1.0;
        }
    } else {
        float clampBuffer = 0.01;
        float outerFade = 1.0 - smoothstep(
                // clamp to keep smoothstep edge 0 below edge 1
                // clampBuffer prevents both edges from being equal
                clamp(outerRadius - v_Fade, 0.0, outerRadius - clampBuffer),
                outerRadius,
                distance
        );

        float innerFade = 1.0;
        // apply inner fade when circle is hollow
        if (innerRadius > 0.0) {
            innerFade = smoothstep(
                    // clamp to keep smoothstep edge 0 below edge 1
                    // clampBuffer prevents both edges from being equal
                    clamp(innerRadius - v_Fade, 0.0, innerRadius - clampBuffer),
                    innerRadius,
                    distance
            );
        }

        alpha = innerFade * outerFade;
    }

    FragColor = vec4(v_Color.rgb, v_Color.a * alpha);
}