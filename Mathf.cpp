#include "Mathf.h"

float garbage::Mathf::MultiplyAdd(float x, float y, float z)
{
#ifdef FP_FAST_FMA
	return fma(x, y, z);
#else
	return x * y + z;
#endif
}