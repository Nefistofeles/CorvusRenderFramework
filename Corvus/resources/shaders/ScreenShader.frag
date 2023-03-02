#version 330 core

in vec2 uv ;
out vec4 outColor ;

uniform sampler2D sampler ;

const float offset = 1.0 / (1000.0) ;

void main()
{
	vec2 offsets[9];
	offsets[0] = vec2(-offset, offset);
	offsets[1] = vec2(  0.0  , offset);
	offsets[2] = vec2( offset, offset);
	offsets[3] = vec2(-offset,  0.0  );
	offsets[4] = vec2(  0.0  ,  0.0  );
	offsets[5] = vec2( offset,  0.0	 );
	offsets[6] = vec2(-offset,-offset);
	offsets[7] = vec2(  0.0	 ,-offset);
	offsets[8] = vec2( offset,-offset);

	float kernel[9] = float[](
       -1.0, -1.0, -1.0,
       -1.0,  9.0, -1.0,
       -1.0, -1.0, -1.0
    );
	vec3 result[9];
	for(int i = 0 ; i < 9 ; i++)
	{
		result[i] = texture(sampler, uv + offsets[i]).rgb;
	}
	vec3 color = vec3(0.0, 0.0, 0.0);
	for(int i = 0 ; i < 9 ; i++)
	{
		color += result[i] * kernel[i] ;
	}
	outColor = vec4(color, 1.0);
}