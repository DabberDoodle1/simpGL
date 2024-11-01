#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 input_color;

uniform mat4 model, view, projection;

void main()
{
  gl_Position = projection * view * model * vec4(pos, 1.0f);
  input_color = color;
}
