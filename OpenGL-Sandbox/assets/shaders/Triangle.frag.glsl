#version 450 core

in vec4 gs_color;
out vec4 color;

void main(void)
{
	color = gs_color; // vec4(0.8, 0.2, 0.3, 1.0);// tes_color;
}