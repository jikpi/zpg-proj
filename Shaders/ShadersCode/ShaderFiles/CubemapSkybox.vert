#version 330
layout (location = 0) in vec3 vp; //vertex position

out vec3 toFrag_textureCoords;

uniform mat4 modelMatrix; //model matrix
uniform mat4 viewMatrix; //camera view matrix
uniform mat4 projectionMatrix; //camera projection matrix

void main() {
    toFrag_textureCoords = vp;
    mat4 view = mat4(mat3(viewMatrix)); //remove translation from view matrix
    vec4 position = projectionMatrix * view * modelMatrix * vec4(vp, 1.0);
    gl_Position = position.xyww; //render to far plane
}
