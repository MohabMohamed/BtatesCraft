#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout (location = 2) in vec3 iOffset;
uniform mat4 MVP;
out vec2 v_texcoord;
void main()
{
	gl_Position =MVP * vec4(position + iOffset, 1);
	v_texcoord = texcoord;
}

#shader fragment
#version 330 core

out vec4 color;
in vec2 v_texcoord;
uniform sampler2D u_texture;
void main()
{
	color = texture (u_texture, v_texcoord);
	 
}