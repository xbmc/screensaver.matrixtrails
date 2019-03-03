#version 150

in vec3 a_pos;
in vec4 a_color;
in vec2 a_coord;

out vec2 v_coord;
out vec4 v_color;

void main ()
{
  gl_Position = vec4(a_pos, 1.0);
  v_color = a_color;
  v_coord = a_coord;
}
