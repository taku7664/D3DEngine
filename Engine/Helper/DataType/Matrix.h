#pragma once

class Matrix4X4F : public DirectX::SimpleMath::Matrix
{
	using DirectX::SimpleMath::Matrix::Matrix;
};

#ifdef _D2D1_H_
class Matrix3X2F : public D2D1_MATRIX_3X2_F
{
	using D2D1_MATRIX_3X2_F::D2D1_MATRIX_3X2_F;
};
#endif