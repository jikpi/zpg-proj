#version 330

in vec3 toFrag_textureCoords;

out vec4 out_frag_Color;


uniform samplerCube cubemapTexture;

void main () {
    vec2 screenCenter = vec2(gl_FragCoord.x / 1700.0, gl_FragCoord.y / 900.0);
    float radius = 0.001;
    if (distance(screenCenter, vec2(0.5, 0.5)) < radius) {
        out_frag_Color = vec4(1.0, 1.0, 1.0, 1.0);
    } else
    out_frag_Color =  texture(cubemapTexture, toFrag_textureCoords);
}
