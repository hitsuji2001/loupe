#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec4 color;
out vec2 textCoord;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  color = vec4(aColor.x * cos(time), aColor.y * sin(time), aColor.z * cos(sin(time)), 1.0f);
  textCoord = vec2(aTextCoord.x, (1.0f - aTextCoord.y));
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
