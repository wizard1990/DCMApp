#pragma once
#include "ImageMatrix.h"
class DCMDisplayUtil
{
public:
	DCMDisplayUtil(void);
	~DCMDisplayUtil(void);
	static void displayMatrix(CDC* pDC, ImageMatrix* imgMatrix, int x, int y, double size, bool isReverse);
};

