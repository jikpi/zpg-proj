#version 330

in vec3 toFrag_textureCoords;

out vec4 out_frag_Color;


uniform samplerCube cubemapTexture;

void main () {
    out_frag_Color =  texture(cubemapTexture, toFrag_textureCoords);
}
