#version 420					
///
/// MENU VERTEX SHADER
///

attribute vec2 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;
varying vec2 v_texCoord;
varying vec4 v_color;
uniform mat4 u_mvp;

void main()
{
   gl_Position = u_mvp * vec4(a_position, 0.0, 1.0);
   v_texCoord = a_texCoord;
   v_color = a_color;
}