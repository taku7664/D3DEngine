#pragma once

class ColorF
{
public:
	ColorF(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 1.0f)
		: r(_r), g(_g), b(_b), a(_a) {}
public:
	float r, g, b, a;

	UINT32 GetRGB()
	{
		UINT8 r_ = static_cast<UINT8>(r * 255.0f);
		UINT8 g_ = static_cast<UINT8>(g * 255.0f);
		UINT8 b_ = static_cast<UINT8>(b * 255.0f);
		return (r_ << 16) | (g_ << 8) | (b_);
	}

	operator const float* () const { return &r; }
	operator const Vector4() const { return Vector4(r, g, b, a); }
#ifdef _D2D1_H_
	operator D3DCOLORVALUE()
	{
		return D3DCOLORVALUE(r, g, b, a);
	}
#endif
};