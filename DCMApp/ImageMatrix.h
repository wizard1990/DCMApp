#pragma once
#include "DCMHeaders.h"

class ImageMatrix
{
private:
	Uint16 mRows;
	Uint16 mColumns;
	Uint16 *mPixData16;
	Uint8 *mPixData8;
	double mWindowCenter;
	double mWindowWidth;
	int mPixLength;

public:
	ImageMatrix(void);
	ImageMatrix(DcmDataset *dataset);
	~ImageMatrix(void);

	Uint16 getRows();
	Uint16 getColumns();
	double getWinCenter();
	double getWinWidth();

	//get pixel data of the position
	Uint8 getUint8Pixel(int row, int column);
	Uint16 getUint16Pixel(int row, int column);
	void setUint16Pixel(int row, int column, Uint16 pixelValue);

	Uint8* getUint8Data();
	Uint16* getUint16Data();

	CString mContentTime;
	CString mTestInfo;
	Uint8 mIndex;
	Float64 pixelSpacing;
	Float64 sliceThickness;
	Float32 PWICoe;
};

