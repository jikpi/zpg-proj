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

void main () {
    //(n) for Idiffuse, normalised normal
    vec3 n_ = normalize(toFrag_worldNormal);

    // ### Iambient,       Ia       *      ra
    vec3 combinedColor = ambientColor * diffuseColor;// ambient light color added to the result

    // (c) for Ispecular, direction from fragment to camera
    vec3 c_ = normalize(toFrag_eyePosition - toFrag_worldPosition.xyz);

    // Point lights
    for (int i = 0; i < LightPointSize; i++) {
        // (l) for Idiffuse, normalized direction from the surface point to the light source
        vec3 l_ = normalize(LightPointArray[i].position - toFrag_worldPosition.xyz);

        float distance = length(LightPointArray[i].position - toFrag_worldPosition.xyz);//distance from light to fragment
        float attn = 1.0 / (LightPointArray[i].constant + LightPointArray[i].linear *
        distance + LightPointArray[i].quadratic * distance * distance);//attenuation

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0);//how strong the light is based on the angle


        // (r_) for Ispecular, reflection direction.
        vec3 r_;

        // Check if the light is behind the fragment
        if (diffuse_dotp_nonmaxd < 0.0)
        {
            r_ = vec3(0.0, 0.0, 0.0);
        }
        else
        {
            r_ = reflect(-l_, n_);
        }

        // ### Idiffuse             Id       *      rd     *     max(0,n_ x l_)
        vec3 Idiffuse = LightPointArray[i].color * diffuseColor * diffuse_dotp_maxd;

        // Is
        vec3 Is = LightPointArray[i].color * LightPointArray[i].intensity;

        // ### Ispecular  Is *       rs     *     max(0,r_ x c_)^shineValue
        vec3 Ispecular = Is * specularColor * pow(max(dot(r_, c_), 0.0), shineValue);

        // Sum the diffuse and specular components, ambient is added once
        combinedColor += (Idiffuse + Ispecular) * attn;
    }

    // Directional lights
    for (int i = 0; i < LightDirectionalSize; i++) {
        // (l) for Idiffuse, the direction from the light source
        vec3 l_ = normalize(-LightDirectionalArray[i].direction);//negated direction

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0);//how strong the light is based on the angle

        // (r_) for Ispecular, reflection direction.
        vec3 r_;
        if (diffuse_dotp_nonmaxd < 0.0) {
            r_ = vec3(0.0, 0.0, 0.0);
        } else {
            r_ = reflect(-l_, n_);
        }

        // ### Idiffuse             Id                 *       rd     *     max(0,n_ x l_)
        vec3 Idiffuse = LightDirectionalArray[i].color * diffuseColor * diffuse_dotp_maxd;
        Idiffuse *= LightDirectionalArray[i].intensity;

        // Is
        vec3 Is = LightDirectionalArray[i].color * LightDirectionalArray[i].intensity;

        // ### Ispecular  Is *       rs     *     max(0,r_ x c_)^shineValue
        vec3 Ispecular = Is * specularColor * pow(max(dot(r_, c_), 0.0), shineValue);

        // Sum the diffuse and specular components, ambient is added once
        combinedColor += (Idiffuse + Ispecular);
    }

    // Spotlights
    for (int i = 0; i < LightSpotSize; i++) {
        // (l) for Idiffuse, normalized direction from the surface point to the light source
        vec3 l_ = normalize(LightSpotArray[i].position - toFrag_worldPosition.xyz);

        //Spot light specific
        float theta = dot(l_, normalize(-LightSpotArray[i].direction));// angle between light and fragment
        float epsilon = LightSpotArray[i].innerCutOff - LightSpotArray[i].outerCutOff;//inner and outer cutoff angle difference
        float intensity = clamp((theta - LightSpotArray[i].outerCutOff) / epsilon, 0.0, 1.0);// intensity based on angle

        //Attn
        float distance = length(LightSpotArray[i].position - toFrag_worldPosition.xyz);//distance from light to fragment
        float attn = 1.0 / (LightSpotArray[i].constant + LightSpotArray[i].linear *
        distance + LightSpotArray[i].quadratic * distance * distance);//attenuation

        float diffuse_dotp_nonmaxd = dot(n_, l_);
        float diffuse_dotp_maxd = max(diffuse_dotp_nonmaxd, 0.0);//how strong the light is based on the angle

        // (r_) for Ispecular, reflection direction.
        vec3 r_;
        if (diffuse_dotp_nonmaxd < 0.0) {
            r_ = vec3(0.0, 0.0, 0.0);
        } else {
            r_ = reflect(-l_, n_);
        }

        // ### Idiffuse             Id          *       rd     *     max(0,n_ x l_)
        vec3 Idiffuse = LightSpotArray[i].color * diffuseColor * diffuse_dotp_maxd;
        Idiffuse *= LightSpotArray[i].intensity;

        // Is
        vec3 Is = LightSpotArray[i].color * LightSpotArray[i].intensity;

        // ### Ispecular  Is *       rs     *     max(0,r_ x c_)^shineValue
        vec3 Ispecular = Is * specularColor * pow(max(dot(r_, c_), 0.0), shineValue);

        // Sum
        combinedColor += (Idiffuse + Ispecular) * attn * intensity;
    }

    out_frag_Color = vec4(combinedColor, 1.0);
}
