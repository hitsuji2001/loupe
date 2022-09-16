#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;
layout (location = 2) in vec3 aColor;

out vec4 color;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
  textCoord = vec2(aTextCoord.x, aTextCoord.y);
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
