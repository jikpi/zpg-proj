#version 330
const int LIGHTS_SIZE_MAX = 16;

in vec3 toFrag_worldNormal;//transformed normal from vertex shader, lighting
in vec4 toFrag_worldPosition;//world position from vertex shader, lighting
in vec3 toFrag_eyePosition;//camera position for fragment shader

out vec4 out_frag_Color;


uniform vec3 diffuseColor = vec3(0.3, 0.3, 1.0);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);// ambient color
uniform vec3 specularColor = vec3(1.0, 1.0, 1.0);// spec color
uniform float shineValue = 255;//10 - 256, more shine

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

    vec3 viewDirection = normalize(toFrag_eyePosition - toFrag_worldPosition.xyz);

    for (int i = 0; i < lightsArraySize; i++) {
        vec3 lightDirection = normalize(lightsArray[i].position - toFrag_worldPosition.xyz);

        float distance = length(lightsArray[i].position - toFrag_worldPosition.xyz);//distance from light to fragment
        float attn = 1.0 / (lightsArray[i].constant + lightsArray[i].linear *
        distance + lightsArray[i].quadratic * distance * distance);//attenuation

        float interDot = dot(normalizedNormal, lightDirection);
        float dot_product = max(interDot, 0.0);//how strong the light is based on the angle

        vec3 halfwayDir = normalize(lightDirection + viewDirection);

        //check if light is behind the fragment
        float spec; //specular  strength
        if(interDot < 0.0) {
            spec = 0.0;
        } else {
            spec = pow(max(dot(normalizedNormal, halfwayDir), 0.0), shineValue);//specular strength
        }

        combinedColor += (dot_product * diffuseColor * lightsArray[i].color + spec * specularColor) * lightsArray[i].intensity * attn;
    }

    out_frag_Color = vec4(combinedColor, 1.0);
}