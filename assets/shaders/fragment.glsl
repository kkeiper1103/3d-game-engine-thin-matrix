#version 400 core

in vec2 pass_textureCoords;

out vec4 FragColor;

uniform sampler2D textureSampler;

void main() {
    FragColor = texture(textureSampler, pass_textureCoords);
}
