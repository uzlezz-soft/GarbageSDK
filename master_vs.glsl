#version 330 core

// vertex shader

{DEFINES}

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

uniform mat4 camMatrix;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

uniform float time;

out struct VertexOutput
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texcoord;
} vs_out;

void main()
{
	vs_out.position = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0));
	vs_out.normal = aNormal;
	vs_out.color = aColor;
	vs_out.texcoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

	gl_Position = camMatrix * vec4(vs_out.position, 1.0f);
}
