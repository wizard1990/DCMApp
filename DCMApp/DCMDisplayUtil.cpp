#include "StdAfx.h"
#include "DCMDisplayUtil.h"


DCMDisplayUtil::DCMDisplayUtil(void)
{
}


DCMDisplayUtil::~DCMDisplayUtil(void)
{
}

void DCMDisplayUtil::displayMatrix(CDC* pDC, ImageMatrix* imgMatrix, int x, int y, double size, bool isReverse)
{
	Uint16 columns = imgMatrix->getColumns();
	Uint16 rows = imgMatrix->getRows();
	Uint16 *originData = imgMatrix->getUint16Data();
	int count = columns * rows;
	double winCenter = imgMatrix->getWinCenter();
	double winWidth = imgMatrix->getWinWidth();
	Uint8 *pData = (Uint8 *)malloc(sizeof(Uint8) * count);

	LPBITMAPINFO m_lpBMIH;
	m_lpBMIH = (LPBITMAPINFO) new char [sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256];
		m_lpBMIH->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_lpBMIH->bmiHeader.biWidth = columns;
		m_lpBMIH->bmiHeader.biHeight = rows;
		m_lpBMIH->bmiHeader.biPlanes = 1;
		m_lpBMIH->bmiHeader.biBitCount = 8;
		m_lpBMIH->bmiHeader.biCompression = BI_RGB;
		m_lpBMIH->bmiHeader.biSizeImage = columns * rows;
		m_lpBMIH->bmiHeader.biXPelsPerMeter = 0;
		m_lpBMIH->bmiHeader.biYPelsPerMeter = 0;
		for (int i = 0; i < 256; i ++) { 
			m_lpBMIH->bmiColors[i].rgbRed = i; 
			m_lpBMIH->bmiColors[i].rgbGreen = i; 
			m_lpBMIH->bmiColors[i].rgbBlue = i; 
			m_lpBMIH->bmiColors[i].rgbReserved = 0; 
		}

		for(int i = 0;i < count; i++){
			int j = (rows - 1 - i / columns) * columns + i % columns;
			//左上到右下变为左下到右上
			if(originData[i] < winCenter - winWidth / 2.0) pData[j] = 0;
			else if(originData[i] < winCenter + winWidth / 2.0) 
				pData[j] = int(255.0 / winWidth * (originData[i] + winWidth / 2.0 - winCenter));
			else pData[j] = 255;
			if (isReverse) pData[j] = 255 - pData[j];
		}
		StretchDIBits(pDC->GetSafeHdc(), x, y, int(m_lpBMIH->bmiHeader.biWidth * size), int(m_lpBMIH->bmiHeader.biHeight * size),
		0,0, m_lpBMIH->bmiHeader.biWidth, m_lpBMIH->bmiHeader.biHeight, 
		pData, (LPBITMAPINFO)m_lpBMIH, DIB_RGB_COLORS, SRCCOPY);
		
		free(pData);
}