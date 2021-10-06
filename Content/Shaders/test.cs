#version 430 core
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct ParticlePos{
	vec2 pos;
	vec4 color;
};

struct ParticleData{
	float time;
	int behavior;
};

layout(std430, binding=4) buffer Pos
{
	ParticlePos Positions[ ];
};

layout(std430, binding=5) buffer Data
{
	ParticleData Behavior[ ];
};

layout(local_size_x=128, local_size_y = 1, local_size_z = 1) in;

void main(){
	uint gid = gl_GlobalInvocationID.x;

	ParticlePos p = Positions[gid];
	ParticleData c = Behavior[gid];

	//p.x += float(gid) / 1000;
	
	
	c.time += 1.0;
	p.pos.x += sin(float(gid));
	p.pos.y += cos(float(gid));
	//do whatever I want here

	Positions[gid] = p;
	Behavior[gid] = c;
}
