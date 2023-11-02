#version 330
out vec4 out_frag_Color;

uniform vec3 diffuseColor = vec3(0.3, 0.3, 1.0);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);// discarded

void main () {
    out_frag_Color = vec4 (diffuseColor, 1.0);
}