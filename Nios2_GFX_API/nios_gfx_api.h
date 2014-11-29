#ifndef NIOS_GFX_API_H_INCLUDED
#define NIOS_GFX_API_H_INCLUDED

#define CHARACTER_WIDTH 4
#define CHARACTER_HEIGHT 4

/*
    Need to implement:
DONE    rest
		key
		KEY_W
		KEY_S
		KEY_UP
		KEY_DOWN
DONE	clear_keybuf
DONE	clear_to_color
		font
DONE	textout_ex
DONE	acquire_screen
DONE	makecol
DONE    rectfill                                                                     ^
DONE	circlefill
DONE	screen
		draw_sprite
DONE	release_screen
		allegro_init
		install_keyboard
		set_color_depth
		GFX_AUTODETECT_WINDOWED
		set_gfx_mode
		create_bitmap
		KEY_ESC
*/

//TYPEDEFS
typedef short *BITMAP;
typedef short Color;

//MACROS
// Use PIXEL_BUFFER_BASE_ADDR instead
#define screen (short *) 0x00000000
#define draw_sprite(scr_ptr,buf,x,y)
#define rest(t)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

//FUNCTIONS
#define acquire_screen()
#define release_screen()

void rectfill(void *ptr, int x1, int y1, int x2, int y2, Color color);

#define circlefill(ptr, x, y, r, color) rectfill(ptr,(x-r),(y-r),(x+r),(y+r),color)

//0-4b 5-10g 11-15r
#define makecol(r, g, b) ((unsigned short)((r&0xF8)<<8) | (unsigned short)((g&0xFC)<<3) | (unsigned short)((b&0xF8)>>3))

void textout_ex(void *ptr, const char *text_ptr, int x, int y, Color fg, Color bg);

void clear_keybuf();
void readkey();

#define clear_to_color(ptr,c) rectfill(ptr, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, c)


//TODO: Implement framework for reading the keys

#endif // NIOS_GFX_API_H_INCLUDED
