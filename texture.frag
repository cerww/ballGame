#version 130


in vec2 fragposition;
in vec4 fragColor;
in vec2 fragUV;

out vec4 Color;

uniform sampler2D Text;
void main(){
	vec4 textcolour = texture(Text,fragUV);
	Color = fragColor*textcolour;
}