#include "GLUtility.h"


bool GLLoadImage(const wchar_t *filename, int *width, int *height, unsigned char *&p_data)
{
    TG::TGBitmap image;
    image.ReadFile(filename);

	*width = image.Width();
	*height = image.Height();
    int s = 4**width**height;
	p_data = new unsigned char[s];
	memcpy(p_data, image.Pixel(), s);

	return true;
}