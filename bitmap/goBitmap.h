// Copyright 2016 The go-vgo Project Developers. See the COPYRIGHT
// file at the top-level directory of this distribution and at
// https://github.com/go-vgo/robotgo/blob/master/LICENSE
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

// class BMP
// {
// 	public:
// 		size_t width;
// 		size_t height;
// 		size_t byteWidth;
// 		uint8_t bitsPerPixel;
// 		uint8_t bytesPerPixel;
// 		uint8_t *image;
// };
#include "bitmap_class.h"
#include "bitmap_find_c.h"
#include "../base/color_find_c.h"
// #include "../screen/screen_c.h"
#include "../base/io_c.h"
#include "../base/pasteboard_c.h"
#include "../base/str_io_c.h"
#include <assert.h>
#include <stdio.h>

/* Returns false and sets error if |bitmap| is NULL. */
bool bitmap_ready(MMBitmapRef bitmap){
	if (bitmap == NULL || bitmap->imageBuffer == NULL) {
		return false;
	}
	return true;
}

void bitmap_dealloc(MMBitmapRef bitmap){
	if (bitmap != NULL) {
		destroyMMBitmap(bitmap);
		bitmap = NULL;
	}
}

bool bitmap_copy_to_pboard(MMBitmapRef bitmap){
	MMPasteError err;

	if (!bitmap_ready(bitmap)) return false;
	if ((err = copyMMBitmapToPasteboard(bitmap)) != kMMPasteNoError) {
		return false;
	}

	return true;
}

MMBitmapRef bitmap_deepcopy(MMBitmapRef bitmap){
	return bitmap == NULL ? NULL : copyMMBitmap(bitmap);
}

MMPoint aFindBitmap(MMBitmapRef bit_map, MMRect rect){
	// MMRect rect;
	// rect.size.width = 10;
	// rect.size.height = 20;
	// rect.origin.x = 10;
	// rect.origin.y = 20;

	float tolerance = 0.0f;
	MMPoint point;

	tolerance = 0.5;

	if (findBitmapInRect(bit_map, bit_map, &point,
	                     rect, tolerance) == 0) {
		return point;
	}
	return point;
}

MMBitmapRef bitmap_open(char *path, uint16_t ttype){
	// MMImageType type;

	MMBitmapRef bitmap;
	MMIOError err;

	bitmap = newMMBitmapFromFile(path, ttype, &err);
	// printf("....%zd\n", bitmap->width);
	return bitmap;

}

char *bitmap_save(MMBitmapRef bitmap, char *path, uint16_t type){
	if (saveMMBitmapToFile(bitmap, path, (MMImageType) type) != 0) {
		return "Could not save image to file.";
	}else{
		saveMMBitmapToFile(bitmap, path, (MMImageType) type);
	}
	//destroyMMBitmap(bitmap);
	return "ok";
}

char *aTostringBitmap(MMBitmapRef bitmap){
	char *buf = NULL;
	MMBMPStringError err;

	buf = (char *)createStringFromMMBitmap(bitmap, &err);

	return buf;
}

MMBitmapRef aGetPortion(MMBitmapRef bit_map, MMRect rect){
	// MMRect rect;
	MMBitmapRef portion = NULL;

	portion = copyMMBitmapFromPortion(bit_map, rect);
	return portion;
}
