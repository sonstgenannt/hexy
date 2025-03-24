#version 330 core

in vec3 vertexPosition;
in vec4 vertexColor;

// Output (to fragment shader)
out vec4 fragColor;

void main()
{
   fragColor = vertexColor;
   fragColor.a = 1.0; // Set alpha to 1.0 (fully opaque)
   gl_Position = vec4(vertexPosition, 1.0);
}
