#version 130

in vec2 vertPosition;
in vec4 vertColor;
in vec2 vertUV;

out vec2 fragposition;
out vec4 fragColor;
out vec2 fragUV;
uniform mat4 orthiMat;
void main(){
	gl_Position.xy = (orthiMat*vec4(vertPosition,0.0,1.0)).xy;
	//gl_Position.xy=vertPosition;
	gl_Position.z=0.0;
	gl_Position.w=1.0;
	fragposition=vertPosition;
	fragColor=vertColor;
	fragUV =vec2(vertUV.x,1-vertUV.y);
	//fragUV=vertUV;
}