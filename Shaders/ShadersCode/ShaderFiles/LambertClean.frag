#version 330
const int LIGHTS_SIZE_MAX = 16;

in vec3 toFrag_worldNormal;//transformed normal from vertex shader, lighting
in vec4 toFrag_worldPosition;//world position from vertex shader, lighting

out vec4 out_frag_Color;

uniform vec3 diffuseColor = vec3(0.3, 0.3, 1.0);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);//ambient light color

struct LightPoint {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

uniform LightPoint LightPointArray[LIGHTS_SIZE_MAX];
uniform int LightPointSize;

struct LightDirectional {
    vec3 direction;
    vec3 color;
    float intensity;
};

uniform LightDirectional LightDirectionalArray[LIGHTS_SIZE_MAX];
uniform int LightDirectionalSize;

struct LightSpot {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform LightSpot LightSpotArray[LIGHTS_SIZE_MAX];
uniform int LightSpotSize;

// (l) for Idiffuse, normalized direction from the surface point to the light source
vec3 calc_l_(vec3 lightPosition, vec3 fragPosition) {

    return normalize(lightPosition - fragPosition);
}

// Idiffuse Id * rd * max(0,n_ x l_)
vec3 calc_Idiffuse(vec3 lightColor, vec3 diffuseColor, float diffuse_dotp_maxd) {
    // Idiffuse  I    *      rd     *     max(0,n_ x l_)
    return lightColor * diffuseColor * diffuse_dotp_maxd;
}

// Lights attenuation
float calc_attn(vec3 lightPosition, vec3 worldPosition, float constant, float linear, float quadratic) {
    float distance = length(lightPosition - worldPosition); //distance from light to fragment
    return 1.0 / (constant + linear * distance + quadratic * distance * distance);
}

// Spotlight intensity
float calc_spotIntensity(vec3 lightDirection, vec3 l, float innerCutOff, float outerCutOff) {
    float theta = dot(l, normalize(-lightDirection));
    float epsilon = innerCutOff - outerCutOff;
    return clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
}

void main() {
    //(n) for Idiffuse, normalised normal
    vec3 n_ = normalize(toFrag_worldNormal);

    // ### Iambient,       Ia       *      ra
    vec3 combinedColor = ambientColor * diffuseColor;// ambient light color added to the result

    //Point lights
    for (int i = 0; i < LightPointSize; i++) {
        vec3 l_ = calc_l_(LightPointArray[i].position, toFrag_worldPosition.xyz);
        float diffuse_dotp = max(dot(n_, l_), 0.0);//how strong the light is based on the angle

        vec3 Idiffuse = calc_Idiffuse(LightPointArray[i].color, diffuseColor, diffuse_dotp);

        float attn = calc_attn(LightPointArray[i].position, toFrag_worldPosition.xyz,
                               LightPointArray[i].constant, LightPointArray[i].linear, LightPointArray[i].quadratic);

        combinedColor += (Idiffuse * attn);//combine
    }

    //Directional lights
    for (int i = 0; i < LightDirectionalSize; i++) {
        vec3 l_ = -LightDirectionalArray[i].direction;
        float diffuse_dotp = max(dot(n_, l_), 0.0);//how strong the light is based on the angle

        vec3 Idiffuse = calc_Idiffuse(LightDirectionalArray[i].color, diffuseColor, diffuse_dotp);

        combinedColor += Idiffuse;
    }

    //Spot lights
    for (int i = 0; i < LightSpotSize; i++) {
        vec3 l_ = calc_l_(LightSpotArray[i].position, toFrag_worldPosition.xyz);
        float diffuse_dotp = max(dot(n_, l_), 0.0);//how strong the light is based on the angle

        vec3 Idiffuse = calc_Idiffuse(LightSpotArray[i].color, diffuseColor, diffuse_dotp);

        float attn = calc_attn(LightSpotArray[i].position, toFrag_worldPosition.xyz,
                               LightSpotArray[i].constant, LightSpotArray[i].linear, LightSpotArray[i].quadratic);

        float intensity = calc_spotIntensity(LightSpotArray[i].direction, l_, LightSpotArray[i].innerCutOff,
                                             LightSpotArray[i].outerCutOff);

        combinedColor += (Idiffuse * attn * intensity);//combine
    }

    out_frag_Color = vec4(combinedColor, 1.0);
}