#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 textCoord;

uniform sampler2D ourTexture;

void main() {
  FragColor = color * texture(ourTexture, textCoord);
}
