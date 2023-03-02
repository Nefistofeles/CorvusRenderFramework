#pragma once
#include "../graphics/Graphics.h"
using namespace Corvus;

class ScreenBuffer
{
private :
	uint32 fbo = 0, screenTexture = 0, rbo = 0, program = 0;
	uint32 samplerLoc = 0;
public :
	ScreenBuffer(int32 width, int32 height);
	~ScreenBuffer();

	void Start();
	void End();
	void Draw(const float32 color[4]);
};