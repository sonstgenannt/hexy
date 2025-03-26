#version 330

in vec4 fragColor; // This variable name is expected by raylib

uniform float time;
out vec4 final_color;

float delay = 1.0f;
float max_alpha = 0.75f;
float time_scale = 0.8f;
float wavelength = 1.0f;

void main()
{
   final_color = vec4( fragColor.rgb, min(abs(sin(wavelength * max(time - delay, 0.0f))), max_alpha) );
}
