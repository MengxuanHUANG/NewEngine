#pragma once

#ifdef MY_DEBUG
	#define ASSERT(x) if(!(x)) __debugbreak();
#else
	#define ASSERT(x)
#endif