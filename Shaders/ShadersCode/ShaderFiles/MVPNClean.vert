#version 330
layout(location=0) in vec3 vp; //vertex position
layout(location=1) in vec3 vn; //vertex normal

out vec3 toFrag_worldNormal; //transformed normal to fragment shader
out vec4 toFrag_worldPosition; //transformed position to fragment shader
out vec3 toFrag_cameraLocation; //camera position for fragment shader

uniform mat4 modelMatrix; //transformation matrix
uniform mat4 viewMatrix; //camera view matrix
uniform mat4 projectionMatrix; //camera projection matrix
uniform vec3 cameraLocation; //camera location
uniform mat3 normalMatrix; //(M-1)T

void main () {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0); //object to clip space

    toFrag_worldNormal = normalMatrix * vn; //transformed normal for fragment shader, lighting
    toFrag_worldPosition = modelMatrix * vec4(vp, 1.0); //world position for fragment shader, lighting
    toFrag_cameraLocation = cameraLocation; //camera position for fragment shader, lighting
}
