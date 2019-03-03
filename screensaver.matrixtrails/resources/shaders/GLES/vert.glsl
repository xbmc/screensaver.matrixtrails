#version 100

attribute vec3 a_pos;
attribute vec4 a_color;
attribute vec2 a_coord;

varying vec2 v_coord;
varying vec4 v_color;

void main ()
{
  gl_Position = vec4(a_pos, 1.0);
  v_color = a_color;
  v_coord = a_coord;
}
