#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 FragColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

uniform float fakeLighting;

void main() {
    // calculate the texel at given coordinate
    vec4 texel = texture(textureSampler, pass_textureCoords);

    // if the alpha is less than 50%, just discard the pass and move on
    if(texel.a < 0.5) {
        discard;
    }


    // if we're using fakeLighting, replace the normals with a horizontally perpendicular vector
    vec3 actualNormal = surfaceNormal;

    if(fakeLighting > 0.1) {
        actualNormal = vec3(0, 1, 0);
    }


    // get diffuse lighting
    vec3 unitNormal = normalize(actualNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.1); // adds an ambient factor to it

    vec3 diffuse = brightness * lightColor;


    // specular
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specular = dot(reflectedLightDirection, unitVectorToCamera);
    specular = max(specular, 0.0);

    float dampedFactor = pow(specular, shineDamper);
    vec3 finalSpecular = dampedFactor * lightColor * reflectivity;


    // final output
    // diffuse * texture + specular highlights
    FragColor = vec4(diffuse, 1.0) * texel + vec4(finalSpecular, 1.0);
}
