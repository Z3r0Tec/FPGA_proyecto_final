#include "nios_gfx_api.h"

//TODO: finish all missing functions

void rectfill(void *ptr, int x1, int y1, int x2, int y2, Color color ) {
	int offset, row, col;
  	volatile short *pixel_buffer = (short *)ptr; // (short *) 0x00000000;	// VGA pixel buffer
	if(x1 < 0) x1 = 0;
	if(x1 > (SCREEN_WIDTH-1)) x1 = (SCREEN_WIDTH-1);
	if(x2 < 0) x2 = 0;
	if(x2 > (SCREEN_WIDTH-1)) x2 = (SCREEN_WIDTH-1);
	if(y1 < 0) y1 = 0;
	if(y1 > (SCREEN_HEIGHT-1)) y1 = (SCREEN_HEIGHT-1);
	if(y2 < 0) y2 = 0;
	if(y2 > (SCREEN_HEIGHT-1)) y2 = (SCREEN_HEIGHT-1);
	/* assume that the box coordinates are valid */
	for (row = y1; row <= y2; row++)
	{
		col = x1;
		while (col <= x2)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = color;	// compute halfword address, set pixel
			++col;
		}
	}
}

void textout_ex(void *ptr, const char *text_ptr, int x, int y, Color fg, Color bg)
{
	int offset;
	x /= CHARACTER_WIDTH;
	y /= CHARACTER_HEIGHT;

  	volatile char * character_buffer = (char *) 0x00088000;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

void clear_keybuf(){
}

void readkey(){
}
