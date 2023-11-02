#version 330
out vec4 out_frag_Color;

void main () {
    vec3 color = vec3(0.3, 0.3, 1.0);
    out_frag_Color = vec4 (color, 1.0);
}
