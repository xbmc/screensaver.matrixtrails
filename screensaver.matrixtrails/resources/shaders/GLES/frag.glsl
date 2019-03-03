#version 100

precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_coord;
varying vec4 v_color;

void main ()
{
  gl_FragColor = texture2D(u_texture, v_coord) * v_color;
}
