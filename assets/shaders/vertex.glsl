#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

out float visibility;

uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;

const float density = 0.0035;
const float gradient = 5.0;

void main() {
    vec4 worldPosition = transformationMatrix * vec4(position, 1);

    vec4 positionRelativeToCamera = viewMatrix * worldPosition;

    gl_Position = projectionMatrix * positionRelativeToCamera;

    pass_textureCoords = textureCoords;

    surfaceNormal = (transformationMatrix * vec4(normal, 0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;

    // specular lighting for
    toCameraVector = (inverse(viewMatrix) * vec4(0, 0, 0, 1)).xyz - worldPosition.xyz;

    float distance = length( positionRelativeToCamera.xyz );
    visibility = exp( -pow( (distance * density), gradient ) );
    visibility = clamp(visibility, 0, 1);
}
