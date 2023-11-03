#version 330
const int LIGHTS_SIZE_MAX = 16;

in vec3 toFrag_worldNormal;//transformed normal from vertex shader, lighting
in vec4 toFrag_worldPosition;//world position from vertex shader, lighting
in vec3 toFrag_eyePosition;//camera position for fragment shader

out vec4 out_frag_Color;

uniform vec3 diffuseColor = vec3(1.0, 0.0, 0.863);// object color
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);// ambient color
uniform vec3 specularColor = vec3(1.0, 1.0, 1.0);// spec color
uniform float shineValue = 255;//10 - 256, more shine

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

// (r_) for Ispecular, reflection direction.
vec3 cal_r_(vec3 l, vec3 n, float diffuse_dotp_nonmaxd) {
    // Check if the light is behind the fragment
    if (diffuse_dotp_nonmaxd < 0.0) {
        return vec3(0.0, 0.0, 0.0);
    } else {
        return reflect(-l, n);
    }
}

// Lights attenuation
float calc_attn(vec3 lightPosition, vec3 worldPosition, float constant, float linear, float quadratic) {
    float distance = length(lightPosition - worldPosition); //distance from light to fragment
    return 1.0 / (constant + linear * distance + quadratic * distance * distance);
}

// Idiffuse Id * rd * max(0,n_ x l_)
vec3 calc_Idiffuse(vec3 lightColor, vec3 diffuseColor, float diffuse_dotp_maxd) {
    // Idiffuse  I    *      rd     *     max(0,n_ x l_)
    return lightColor * diffuseColor * diffuse_dotp_maxd;
}

// Is
vec3 calc_Is(vec3 lightColor, float lightIntensity) {
    return lightColor * lightIntensity;
}

//Ispecular  Is *  rs * max(0,r_ x c_)^shineValue
vec3 calc_Ispecular(vec3 lightColor, vec3 specularColor, vec3 r_, vec3 c_, float shineValue) {
    //Ispecular  Is   *        rs     *     max(0,r_ x c_)^shineValue
    return lightColor * specularColor * pow(max(dot(r_, c_), 0.0), shineValue);
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

    // (c) for Ispecular, direction from fragment to camera
    vec3 c_ = normalize(toFrag_eyePosition - toFrag_worldPosition.xyz);

    // Point lights
    for (int i = 0; i < LightPointSize; i++) {
        vec3 l_ = calc_l_(LightPointArray[i].position, toFrag_worldPosition.xyz);

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0);//how strong the light is based on the angle
        vec3 r_ = cal_r_(l_, n_, diffuse_dotp_nonmaxd);

        vec3 Idiffuse = calc_Idiffuse(LightPointArray[i].color, diffuseColor, diffuse_dotp_maxd);

        vec3 Is = calc_Is(LightPointArray[i].color, LightPointArray[i].intensity);
        vec3 Ispecular = calc_Ispecular(Is, specularColor, r_, c_, shineValue);

        float attn = calc_attn(LightPointArray[i].position, toFrag_worldPosition.xyz,
                               LightPointArray[i].constant, LightPointArray[i].linear, LightPointArray[i].quadratic);

        // Sum the diffuse and specular components, ambient is added once
        combinedColor += (Idiffuse + Ispecular) * attn;
    }

    // Directional lights
    for (int i = 0; i < LightDirectionalSize; i++) {
        vec3 l_ = normalize(-LightDirectionalArray[i].direction); //negated direction

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0); //how strong the light is based on the angle
        vec3 r_ = (diffuse_dotp_nonmaxd < 0.0) ? vec3(0.0, 0.0, 0.0) : reflect(-l_, n_);

        vec3 Idiffuse = calc_Idiffuse(LightDirectionalArray[i].color, diffuseColor, diffuse_dotp_maxd);

        vec3 Is = calc_Is(LightDirectionalArray[i].color, LightDirectionalArray[i].intensity);
        vec3 Ispecular = calc_Ispecular(Is, specularColor, r_, c_, shineValue);

        // Sum the diffuse and specular components, ambient is added once
        combinedColor += (Idiffuse + Ispecular);
    }


    // Spotlights
    for (int i = 0; i < LightSpotSize; i++) {
        vec3 l_ = calc_l_(LightSpotArray[i].position, toFrag_worldPosition.xyz);

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0); //how strong the light is based on the angle
        vec3 r_ = cal_r_(l_, n_, diffuse_dotp_nonmaxd);

        vec3 Idiffuse = calc_Idiffuse(LightSpotArray[i].color, diffuseColor, diffuse_dotp_maxd);

        vec3 Is = calc_Is(LightSpotArray[i].color, LightSpotArray[i].intensity);
        vec3 Ispecular = calc_Ispecular(Is, specularColor, r_, c_, shineValue);

        float attn = calc_attn(LightSpotArray[i].position, toFrag_worldPosition.xyz,
                               LightSpotArray[i].constant, LightSpotArray[i].linear, LightSpotArray[i].quadratic);
        float intensity = calc_spotIntensity(LightSpotArray[i].direction, l_,
                                             LightSpotArray[i].innerCutOff, LightSpotArray[i].outerCutOff);

        // Sum the diffuse and specular components
        combinedColor += (Idiffuse + Ispecular) * attn * intensity;
    }

    out_frag_Color = vec4(combinedColor, 1.0);
}
