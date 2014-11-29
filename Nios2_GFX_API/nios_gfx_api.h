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
inline void acquire_screen() {}
inline void release_screen() {}

void rectfill(void *ptr, int x1, int y1, int x2, int y2, Color color);

inline void circlefill(void *ptr, int x, int y, int r, Color color){
	rectfill(ptr,(x-r),(y-r),(x+r),(y+r),color);
}

Color makecol(short r, short g, short b);

void textout_ex(void *ptr, const char *text_ptr, int x, int y, Color fg, Color bg);

void clear_keybuf();
void readkey();
void clear_to_color( void *ptr, Color c);


//TODO: Implement framework for reading the keys

#endif // NIOS_GFX_API_H_INCLUDED
