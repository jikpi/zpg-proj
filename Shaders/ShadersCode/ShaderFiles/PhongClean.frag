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
    //(n) for Idiffuse, normalised normal
    vec3 n_ = normalize(toFrag_worldNormal);

    // ### Iambient,       Ia       *      ra
    vec3 combinedColor = ambientColor * diffuseColor; // ambient light color added to the result

    // (c) for Ispecular, direction from fragment to camera
    vec3 c_ = normalize(toFrag_eyePosition - toFrag_worldPosition.xyz);

    for (int i = 0; i < lightsArraySize; i++) {
        // (l) for Idiffuse, normalized direction from the surface point to the light source
        vec3 l_ = normalize(lightsArray[i].position - toFrag_worldPosition.xyz);

        float distance = length(lightsArray[i].position - toFrag_worldPosition.xyz);//distance from light to fragment
        float attn = 1.0 / (lightsArray[i].constant + lightsArray[i].linear *
        distance + lightsArray[i].quadratic * distance * distance);//attenuation

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0);//how strong the light is based on the angle


        // (r_) for Ispecular, reflection direction.
        vec3 r_;

        //check if the light is behind the fragment
        if(diffuse_dotp_nonmaxd < 0.0)
        {
            r_ = vec3(0.0, 0.0, 0.0);
        }
        else
        {
            r_ = reflect(-l_, n_);
        }

        // ### Idiffuse             Id       *      rd     *     max(0,n_ x l_)
        vec3 Idiffuse = lightsArray[i].color * diffuseColor * diffuse_dotp_maxd;

        // Is
        vec3 Is = lightsArray[i].color * lightsArray[i].intensity;

        // ### Ispecular  Is *       rs     *     max(0,r_ x c_)^shineValue
        vec3 Ispecular = Is * specularColor * pow(max(dot(r_,c_), 0.0), shineValue);

        //sum the diffuse and specular components, ambient is added once
        combinedColor += (Idiffuse + Ispecular) * attn;
    }

    out_frag_Color = vec4(combinedColor, 1.0);
}
