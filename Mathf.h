#ifndef _garbage_mathf
#define _garbage_mathf

#include "GarbageSDK.h"
#include <cmath>
#include <algorithm>

namespace garbage
{

	class GSDK Mathf
	{
	public:

		static inline float Pi() { return 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899f; }
		static inline float Pi_2() { return 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899f / 2.f; }
		static float Rad2Deg() { return 1 / Pi() * 180.f; }
		static float Deg2Rad() { return 1 / 180.f * Pi(); }

		static inline float Sin(float x) { return sinf(x); }
		static inline float Cos(float x) { return cosf(x); }
		static inline float Tg(float x) { return tanf(x); }
		static inline float Ctg(float x) { return 1 / tanf(x); }

		static inline float ArcSin(float x) { return asinf(x); }
		static inline float ArcCos(float x) { return acosf(x); }
		static inline float ArcTg(float x) { return atanf(x); }
		static inline float ArcTg2(float y, float x) { return atan2f(y, x); }
		static inline float ArcCtg(float x) { return Pi_2() - atanf(x); }

		static inline float Exp(float x) { return expf(x); }
		static inline float Log(float x) { return logf(x); }
		static inline float Log10(float x) { return log10f(x); }

		static inline float Pow(float x, float exp) { return powf(x, exp); }
		static inline float Sqrt(float x) { return sqrtf(x); }
		static inline float Cbrt(float x) { return cbrtf(x); }
		static inline float Hypotenuse(float x, float y) { return hypotf(x, y); }

		static inline float Min(float x, float y) { return fminf(x, y); }
		static inline float Max(float x, float y) { return fmaxf(x, y); }

		static inline float Ceil(float x) { return ceilf(x); }
		static inline float Floor(float x) { return floorf(x); }
		static inline float FMod(float x, float y) { return fmodf(x, y); }
		static inline float Trunc(float x) { return truncf(x); }
		static inline int Round(float x) { return static_cast<int>(roundf(x)); }
		static inline float CopySign(float number, float sign) { return copysignf(number, sign); }

		static inline float FDim(float x, float y) { return fdimf(x, y); }
		static inline float Abs(float x) { return abs(x); }
		static inline float MultiplyAdd(float x, float y, float z);

		static inline float Clamp(float value, float min, float max) { return Min(min, Max(value, max)); }
		static inline float Clamp01(float value) { return Clamp(value, 0, 1); }
		static inline float Lerp(float a, float b, float t) { return a + Clamp01(t) * (b - a); }
		static inline float LerpUnclamped(float a, float b, float t) { return a + t * (b - a); }

	private:

		Mathf();

	};

}

#endif