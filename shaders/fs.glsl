#version 450 core

out vec4 FragColor;

in vec4 Color;


void main()
{
	FragColor = vec4(Color);
}