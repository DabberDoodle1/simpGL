#version 460 core
in vec3 input_color;
out vec4 frag_color;

void main()
{
  frag_color = vec4(input_color, 1.0f);
}
