#version 330
const int LIGHTS_SIZE_MAX = 16;

in vec3 toFrag_worldNormal;//transformed normal from vertex shader, lighting
in vec4 toFrag_worldPosition;//world position from vertex shader, lighting

out vec4 out_frag_Color;

uniform vec3 diffuseColor = vec3(0.3, 0.3, 1.0);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);//ambient light color

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

uniform Light lightsArray[LIGHTS_SIZE_MAX];
uniform int lightsArraySize;

void main () {
    vec3 normalizedNormal = normalize(toFrag_worldNormal);
    vec3 combinedColor = ambientColor * diffuseColor;//ambient light

    for (int i = 0; i < lightsArraySize; i++) {
        vec3 lightDirection = normalize(lightsArray[i].position - toFrag_worldPosition.xyz);

        float distance = length(lightsArray[i].position - toFrag_worldPosition.xyz);//distance from light to fragment
        float attn = 1.0 / (lightsArray[i].constant + lightsArray[i].linear *
        distance + lightsArray[i].quadratic * distance * distance);//attenuation

        float dot_product = max(dot(normalizedNormal, lightDirection), 0.0);//how strong the light is based on the angle

        vec3 lightPosition = lightsArray[i].position;
        vec3 lightColor = lightsArray[i].color;
        float lightIntensity = lightsArray[i].intensity;

        combinedColor += (dot_product * lightColor * diffuseColor * lightIntensity  * attn);//combine
    }
    out_frag_Color = vec4(combinedColor, 1.0);
}