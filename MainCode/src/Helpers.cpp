//
//
//

#include <i2cEncoderLibV2.h>

#include "Variables.h"
#include "Helpers.h"

bool handleEncoder()
{
	encoderInterupted = false; // Make sure it is always set to false here
	if (encoder->updateStatus()) {
		lastEncPos = currentEncPos;
		currentEncPos = encoder->readCounterFloat();
		if (currentEncPos != lastEncPos)
		{
			Serial.print("Encoder position changed from "); Serial.print(lastEncPos);
			Serial.print(" to "); Serial.println(currentEncPos);
		}
		if (encoder->readStatus(i2cEncoderLibV2::PUSHR)) {
			Serial.println("Push button Released");
		}

		if (encoder->readStatus(i2cEncoderLibV2::PUSHP)) {
			Serial.println("Push button Pressed");
		}

		if (encoder->readStatus(i2cEncoderLibV2::PUSHD)) {
			Serial.println("Double push!");
		}
		return true;
	}
	return false;
}

// Grabbed from the internet
uint8_t *read1bitBMP(char *fname, int* _w, int* _h)
{
	unsigned char head[54]{};
	auto f = fatfs.open(fname);

	// BMP header is 54 bytes
	f.readBytes(head, 54);

	int w = head[18] + (((int)head[19]) << 8) + (((int)head[20]) << 16) + (((int)head[21]) << 24);
	int h = head[22] + (((int)head[23]) << 8) + (((int)head[24]) << 16) + (((int)head[25]) << 24);

	// lines are aligned on 4-byte boundary
	int lineSize = (w / 8 + (w / 8) % 4);
	int imageSize = w * h;

	uint8_t *img = (uint8_t*)malloc(w * h);
	uint8_t *data = (uint8_t*)malloc(imageSize);
	memset(img, 0x00, w*h);
	memset(data, 0x00, w*h);

	// skip the header
	f.seekSet(54);

	// skip palette - two rgb quads, 8 bytes
	f.seekCur(8);

	// read data
	f.readBytes(data, imageSize);
	// decode bits
	int i, j, k, rev_j;
	for (j = 0, rev_j = h - 1; j < h; j++, rev_j--) {
		for (i = 0; i < w / 8; i++) {
			int fpos = j * lineSize + i, pos = rev_j * w + i * 8;
			for (k = 0; k < 8; k++)
				img[pos + (7 - k)] = (data[fpos] >> k) & 1;
		}
	}

	free(data);
	f.close();
	*_w = w; *_h = h;
	return img;
}
