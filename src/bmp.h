#pragma once
#include <stdlib.h>
#include "assert.h"
#include <windows.h>
#include <stdio.h>
#include <list>
#include <algorithm>



#define LOG_OUT(_x_) OutputDebugString(_x_) 
#define LOG_OUT_W(_x_)  OutputDebugStringW(_x_) 
#define LOG_OUT_A(_x_)  OutputDebugStringA(_x_) 

bool LoadBmp(const char* filename, byte** pImage, int *width_, int* height_);
//bool SaveBmp(char* filename, ::byte* pImage, int width, int height);
/*
int _tmain(int argc, char* argv[])
{
	::byte* pLoadImage = nullptr;

	LoadBmp("C:/Users/kimdg/Documents/Visual Studio 2013/Projects/Consol_Test_Project/full_hd_image.bmp", &pLoadImage);

	SaveBmp("C:/Users/kimdg/Documents/Visual Studio 2013/Projects/Consol_Test_Project/hd_image.bmp", pLoadImage, 1920, 1080);

	free(pLoadImage);

	return 0;
}*/

bool LoadBmp(const char* filename, byte** pImage, int *width_,int* height_)
{
	FILE* fp;

	// ��Ʈ�� ���� ����ü
	BITMAPFILEHEADER BMFH;					///< BitMap File Header.
	BITMAPINFOHEADER BMIH;					///< BitMap Info Header.

	fopen_s(&fp, filename, "rb");
	if (nullptr == fp)
	{
		LOG_OUT_A("fopen() error");
		return false;
	}

	// ������ ũ�⸸ŭ ���Ͽ��� �о��, �׸��� ��Ʈ����������� �־���
	fread(&BMFH, sizeof(BITMAPFILEHEADER), 1, fp);
	if (BMFH.bfType != 0x4d42)	// ��Ʈ�� ������ �ƴϸ� �����Ѵ�.
	{
		fclose(fp);
		LOG_OUT_A("not '.bmp' file !!!");
		return false;
	}

	fread(&BMIH, sizeof(BITMAPINFOHEADER), 1, fp);	//��������� �ִ� ũ���� ������ŭ �о
	if (BMIH.biBitCount != 24 || BMIH.biCompression != BI_RGB) //24��Ʈ���� üũ�ϰ�, ������ �ȵǾ� �ִ��� üũ�� ��
	{
		fclose(fp);
		return false;
	}

	int Width = BMIH.biWidth;
	int Height = BMIH.biHeight - 1;
	*width_ = Width;
	*height_ = Height;
	int bytePerScanline = (Width * 3 + 3) & ~3;  // �е�
	int size = BMFH.bfSize;
	printf("<read : %d %d %d>\n", Width, Height,size);
	*pImage = (byte*)malloc(size);
	fread(*pImage, size, 1, fp);  // ������ ������ ���� �о�´�.
	printf("[%d %d]", (int) (*pImage)[0],(int) (*pImage)[1]);
	//*pImage += ::bytePerScanline * Height;

	// FILE*�� ����.
	fclose(fp);

	return true;
}