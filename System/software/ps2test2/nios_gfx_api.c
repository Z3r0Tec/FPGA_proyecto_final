#include "nios_gfx_api.h"
#include "system.h"

#define PIO_0_BASE 0x8b000
#define PS2_0_BASE 0x8b020

char p1_up, p1_down, p2_up, p2_down;

//TODO: finish all missing functions

unsigned int readkey(){
	volatile int * ps2_ptr = (int *) PS2_0_BASE;
	return (unsigned int) *(ps2_ptr);
}

void rectfill(void *ptr, int x1, int y1, int x2, int y2, Color color ) {
	int offset, row, col;
  	volatile short *pixel_buffer = (short *)ptr; // (short *) 0x00000000;	// VGA pixel buffer
	/*if(x1 < 0) x1 = 0;
	if(x1 > (SCREEN_WIDTH-1)) x1 = (SCREEN_WIDTH-1);
	if(x2 < 0) x2 = 0;
	if(x2 > (SCREEN_WIDTH-1)) x2 = (SCREEN_WIDTH-1);
	if(y1 < 0) y1 = 0;
	if(y1 > (SCREEN_HEIGHT-1)) y1 = (SCREEN_HEIGHT-1);
	if(y2 < 0) y2 = 0;
	if(y2 > (SCREEN_HEIGHT-1)) y2 = (SCREEN_HEIGHT-1);*/
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
	p1_up = 0;
	p1_down = 0;
	p2_up = 0;
	p2_down = 0;
}

void refresh_kb(){
	volatile int * ps2_ptr = (short *) PS2_0_BASE;
	int tmpKey = 0;
	int data = 0;
	static short release = 0;
	//char text_buffer[10] = "         \0";
	//char clean_text_buffer[10] = "       \0";
	//int offset = 40;
	//int delay, pending;

	//If a key is pressed, it had to be selected untill the break command is found

	//Read the keyboard data

	//*(ps2_ptr) = 0x0;
	tmpKey =  (unsigned) *(ps2_ptr);
/*
	offset = 40;
	pending = (tmpKey>>16)&0xffff;
	for(delay = 0; delay <= pending; delay ++ )
		{
			//itoa(0, text_buffer);
			//textout_ex( clean_text_buffer, clean_text_buffer, 40, offset, makecol( 255, 255, 255), makecol( 0, 0, 0));
			itoa(tmpKey&0xff, text_buffer);
			textout_ex( text_buffer, text_buffer, 40, offset, makecol( 255, 255, 255), makecol( 0, 0, 0));
			offset = offset + 4;
			tmpKey =  (unsigned) *(ps2_ptr);
		}
	//for(delay =0; delay < 5; delay++);
*/
	while ((tmpKey>>16)&0xffff)
	{

		//Extract the buffer data
		data = tmpKey & 0xff;

		if(tmpKey & 0x8000){ //If data valid
			//If the break command is found, we need to check if the next command is one of the keys of interest
			if(data == BREAK_KEY || release == 1){
				if(release){
					release = 0;
				}else{
					tmpKey =  (unsigned) *(ps2_ptr); //Read next
					data = tmpKey & 0xff;
					if(!((tmpKey>>16)&0xffff)){
					    release = 1;
					    break;
					}
				}
				if(data == P1_UP_KEY){
					p1_up = 0;
			//		break;
				}else if(data == P1_DOWN_KEY){
					p1_down = 0;
			//		break;
				}else if(data == P2_UP_KEY){
					p2_up = 0;
			//		break;
				}else if(data == P2_DOWN_KEY){
					p2_down = 0;
			//		break;
				}
			}else{
				if(data == P1_UP_KEY){
					p1_up = 1;
					p1_down = 0;
			//		break;
				}else if(data == P1_DOWN_KEY){
					p1_down = 1;
					p1_up = 0;
			//		break;
				}else if(data == P2_UP_KEY){
					p2_up = 1;
					p2_down = 0;
			//		break;
				}else if(data == P2_DOWN_KEY){
					p2_down = 1;
					p2_up = 0;
				}
			}
		}
		//read again
		tmpKey =  (unsigned) *(ps2_ptr);
	}
}

int key(short index){

	/*
	volatile short * pio_ptr = (short *) PIO_0_BASE;
	return !((*pio_ptr)&index);
	*/

	char return_data;

	if (index == P1_UP){
		return_data = p1_up;
	}else if (index == P1_DOWN){
		return_data = p1_down;
	}else if (index == P2_UP){
		return_data = p2_up;
	}else if (index == P2_DOWN){
		return_data = p2_down;
	}

	return return_data;
}

/*********************************
 * Draw the field
********************************/

void draw_field(Color color){
	//x1 y1 x2 y2
	rectfill(screen, 0, 0, SCREEN_WIDTH-1, 20, color); //top
	rectfill(screen, 0, 0, 5, SCREEN_HEIGHT-1, color); //Left
	rectfill(screen, SCREEN_WIDTH-6, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, color); //Right
	rectfill(screen, 0, SCREEN_HEIGHT-6, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, color); //Bottom

	//Mid field
	//rectfill(screen, SCREEN_WIDTH/2-1, 0, SCREEN_WIDTH/2+1, SCREEN_HEIGHT-1, color); //Left
}

/* itoa:  convert n to characters in s */
void itoa( int n, char s[])
{
	 int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
