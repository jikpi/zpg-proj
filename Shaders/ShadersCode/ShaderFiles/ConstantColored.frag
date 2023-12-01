#version 330
out vec4 out_frag_Color;

uniform vec3 diffuseColor = vec3(0.3, 0.3, 1.0);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);// discarded

void main () {
    vec2 screenCenter = vec2(gl_FragCoord.x / 1700.0, gl_FragCoord.y / 900.0);
    float radius = 0.001;
    if (distance(screenCenter, vec2(0.5, 0.5)) < radius) {
        out_frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
    } else
    out_frag_Color = vec4 (diffuseColor, 1.0);
}