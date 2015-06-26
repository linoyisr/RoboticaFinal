/*
 * pngUtil.h
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>

#define BLACK 0
#define WHITE 255

#define FREE    0
#define OCCUPIED 1
#define UNKNOWN 2

enum CellOffset
{
	ROFFSET = 0,
	GOFFSET = 1,
	BOFFSET = 2,
	AOFFSET = 3
};

namespace  pngUtil
{
	void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
	void decodeOneStep(const char* filename);
//	void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename);
	unsigned char getColorOfPixel(const std::vector<unsigned char>& grid, unsigned int width, unsigned int height, unsigned int row, unsigned int col);
}
#endif /* PNGUTIL_H_ */
