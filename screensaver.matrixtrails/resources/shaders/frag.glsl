#version 150

in vec4 m_col;
in vec2 m_cord;
out vec4 fragColor;

uniform sampler2D tex;

void main ()
{
  fragColor.rgba = vec4(texture(tex, m_cord).rgba * m_col);
}
