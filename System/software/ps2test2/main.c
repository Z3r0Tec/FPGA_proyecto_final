// Pong game modified to compile under NIOS2 with NIOS2 GFX API

//Use next line to compile for PC in order to debug (requires allegro 4.2.2)
//#define USE_ALLEGRO
#include "system.h"

#ifdef USE_ALLEGRO
#include <allegro.h>
#else
#include "nios_gfx_api.h"
#endif // USE_ALLEGRO

//#include <stdio.h>
//#include <cstdlib>
//#include <time.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BAR_HEIGHT 30
#define BAR_WIDTH 5

#define BALL_R 3

#define PADDLE_H_MARGING 10
#define PS2_0_BASE 0x8b020

int ball_x = SCREEN_WIDTH/2;
int ball_y = SCREEN_HEIGHT/2;

int ball_tempX = SCREEN_WIDTH/2;
int ball_tempY = SCREEN_HEIGHT/2;

int p1_x = PADDLE_H_MARGING;
int p1_y = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

int p1_tempX = PADDLE_H_MARGING;
int p1_tempY = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

int p2_x = SCREEN_WIDTH - PADDLE_H_MARGING - BAR_WIDTH;
int p2_y = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

int p2_tempX = SCREEN_WIDTH - PADDLE_H_MARGING - BAR_WIDTH;
int p2_tempY = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

int player1Score, player2Score;
int delay = 0;
int max_delay = 10;
char p1_moved, p2_moved;
//time_t secs;    //The seconds on the system clock will be stored here
                //this will be used as the seed for srand()

int dir;     //This will keep track of the circles direction
            //1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

BITMAP *buffer = screen ; //This will be our temporary bitmap for double buffering

void moveBall(){

    ball_tempX = ball_x;
    ball_tempY = ball_y;

    if (dir == 1 && ball_x > BALL_R && ball_y > BALL_R + 21 ){

         if( ball_x == (p1_x + BAR_WIDTH + BALL_R+1) && ball_y >= p1_y && ball_y < p1_y + BAR_HEIGHT){
                  dir = 3;
         }else{
                 --ball_x;
                 --ball_y;
         }

    } else if (dir == 2 && ball_x > BALL_R && ball_y < (SCREEN_HEIGHT-BALL_R-7)){

         if( ball_x == (p1_x + BAR_WIDTH + BALL_R+1) && ball_y >= p1_y && ball_y < p1_y + BAR_HEIGHT){
                  dir = 4;
         }else{
                 --ball_x;
                 ++ball_y;
         }

    } else if (dir == 3 && ball_x < (SCREEN_WIDTH-BALL_R-2) && ball_y > BALL_R + 21 ){

         if( ball_x + BALL_R == p2_x-1 && ball_y >= p2_y && ball_y < p2_y + BAR_HEIGHT){
                  dir = 1;
         }else{
                 ++ball_x;
                 --ball_y;
         }

    } else if (dir == 4 && ball_x < (SCREEN_WIDTH-BALL_R-2) && ball_y < (SCREEN_HEIGHT-BALL_R -7)){

         if( ball_x + BALL_R == p2_x-1 && ball_y >= p2_y && ball_y < p2_y + BAR_HEIGHT){
                  dir = 2;
         }else{
                 ++ball_x;
                 ++ball_y;
         }

    } else {

        if (dir == 1 || dir == 3)    ++dir;
        else if (dir == 2 || dir == 4)    --dir;

    }

#ifdef USE_ALLEGRO
    acquire_screen();
#endif // USE_ALLEGRO
    circlefill ( buffer, ball_tempX, ball_tempY, BALL_R, makecol( 0, 0, 0));
    circlefill ( buffer, ball_x, ball_y, BALL_R, makecol( 128, 255, 0));
#ifdef USE_ALLEGRO
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
    rest(5);
#else
    /////////// <<<<<<<<<-------------- add delay here???
#endif // USE_ALLEGRO

}

void p1Move(){
    p1_tempY = p1_y;

    if(key(P1_UP) || key(P1_DOWN) ){
    	p1_moved = 1;
    }else{
    	p1_moved = 0;
    }

////TODO: How to read keys from keyboard in NIOS2??
    if( key(P1_UP) && p1_y > 21){

        --p1_y;

    } else if( key(P1_DOWN) && p1_y < (SCREEN_HEIGHT-BAR_HEIGHT-7)){

        ++p1_y;

    }

    if (p1_moved) {
#ifdef USE_ALLEGRO
    acquire_screen();
#endif // USE_ALLEGRO
    rectfill( buffer, p1_tempX, p1_tempY, p1_tempX + BAR_WIDTH, p1_tempY + BAR_HEIGHT, makecol ( 0, 0, 0));
    rectfill( buffer, p1_x, p1_y, p1_x + BAR_WIDTH, p1_y + BAR_HEIGHT, makecol ( 0, 0, 255));
#ifdef USE_ALLEGRO
    release_screen();
#endif

    }
}

void p2Move(){

    p2_tempY = p2_y;
    if(key(P2_UP) || key(P2_DOWN) ){
    	p2_moved = 1;
    }else{
    	p2_moved = 0;
    }
////TODO: How to read keys from keyboard in NIOS2??
    if( key(P2_UP) && p2_y > 21){

        --p2_y;

    } else if( key(P2_DOWN) && p2_y < (SCREEN_HEIGHT-BAR_HEIGHT-7)){

        ++p2_y;

    }
    if (p2_moved) {
#ifdef USE_ALLEGRO
    acquire_screen();
#endif // USE_ALLEGRO
    rectfill( buffer, p2_tempX, p2_tempY, p2_tempX + BAR_WIDTH, p2_tempY + BAR_HEIGHT, makecol ( 0, 0, 0));
    rectfill( buffer, p2_x, p2_y, p2_x + BAR_WIDTH, p2_y + BAR_HEIGHT, makecol ( 0, 0, 255));
#ifdef USE_ALLEGRO
    release_screen();
#endif // USE_ALLEGRO
    }
}


void startNew(){

#ifdef USE_ALLEGRO
    clear_keybuf();
    readkey();
#endif // USE_ALLEGRO
    clear_keybuf();
    readkey();
    clear_to_color( buffer, makecol( 0, 0, 0));  /// We might to want to port this one too
    draw_field(makecol ( 50, 50, 50));
    ball_x = SCREEN_WIDTH/2;
    ball_y = SCREEN_HEIGHT/2;

    p1_x = PADDLE_H_MARGING;
    p1_y = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

    p2_x = SCREEN_WIDTH - BAR_WIDTH - PADDLE_H_MARGING;
    p2_y = (SCREEN_HEIGHT/2) - (BAR_HEIGHT/2);

    rectfill( buffer, p1_x, p1_y, p1_x + BAR_WIDTH, p1_y + BAR_HEIGHT, makecol ( 0, 0, 255));
    rectfill( buffer, p2_x, p2_y, p2_x + BAR_WIDTH, p2_y + BAR_HEIGHT, makecol ( 0, 0, 255));
}

void checkWin(){
	const char *win_p2_text_message = "WINNER: Player 2\0";
	const char *win_p1_text_message = "WINNER: Player 1\0";

    if ( ball_x < p1_x){
 //       textout_ex( screen, "Player 2 Wins!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, makecol( 255, 0, 0), makecol( 0, 0, 0));
        player2Score++;
        startNew();
    } else if ( ball_x > p2_x){
    //    textout_ex( screen, "Player 1 Wins!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, makecol( 255, 0, 0), makecol( 0, 0, 0));
        player1Score++;
        startNew();
    }

    if(player1Score >= 10 || player2Score >= 10 ){

    	if(player1Score >= 10){
    		textout_ex( win_p1_text_message, win_p1_text_message, SCREEN_WIDTH/2-35,SCREEN_HEIGHT/2-15, makecol( 255, 255, 255), makecol( 0, 0, 0));
    	}else {
    		textout_ex( win_p2_text_message, win_p2_text_message, SCREEN_WIDTH/2-35, SCREEN_HEIGHT/2-15, makecol( 255, 255, 255), makecol( 0, 0, 0));
    	}

    	drawScore();

    	player1Score = 0;
    	player2Score = 0;

    	while(1);  //End of game => Press reset to restart.
    }


}

void setupGame(){
#ifdef USE_ALLEGRO
    acquire_screen();
#endif // USE_ALLEGRO
    clear_keybuf();
    clear_to_color(buffer, makecol(0,0,0));
    draw_field(makecol ( 50, 50, 50));
    rectfill( buffer, p1_x, p1_y, p1_x + BAR_WIDTH, p1_y + BAR_HEIGHT, makecol ( 0, 0, 255));
    rectfill( buffer, p2_x, p2_y, p2_x + BAR_WIDTH, p2_y + BAR_HEIGHT, makecol ( 0, 0, 255));
    circlefill ( buffer, ball_x, ball_y, BALL_R, makecol( 128, 255, 0));
#ifdef USE_ALLEGRO
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
#endif // USE_ALLEGRO
    //time(&secs);
    //srand( (unsigned int)secs);
    dir = 1; //rand() % 4 + 1;
    player1Score = 0, player2Score = 0;
}

void drawScore(){
    char p1_buffer[10] = "\0";
    char p2_buffer[10]= "\0";

    char p1_text_buffer[15] = "Player 1:     \0";
    char p2_text_buffer[15]=  "Player 2:     \0";

	static char score_buffer[25];
    itoa(player1Score, p1_buffer);
    itoa(player2Score, p2_buffer);

    //Player 1
    textout_ex( p1_buffer, p1_text_buffer, 40, 15, makecol( 255, 255, 255), makecol( 0, 0, 0));
    textout_ex( p1_buffer, p1_buffer, 80, 15, makecol( 255, 255, 255), makecol( 0, 0, 0));

    //Player 2:
    textout_ex( p2_buffer, p2_text_buffer, SCREEN_WIDTH - 120, 15, makecol( 255, 255, 255), makecol( 0, 0, 0));
    textout_ex( p2_buffer, p2_buffer, SCREEN_WIDTH - 80, 15, makecol( 255, 255, 255), makecol( 0, 0, 0));
    // textout_ex( p2_buffer, p2_buffer, 40, 42, makecol( 255, 255, 255), makecol( 0, 0, 0));
   // sprintf(score_buffer,"P1: %4d P2: %4d",player1Score,player2Score);
   // textout_ex( buffer, score_buffer, PADDLE_H_MARGING*2, PADDLE_H_MARGING*2, makecol( 255, 255, 255), makecol( 0, 0, 0));
}


int main(){
#ifdef USE_ALLEGRO
    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    buffer = create_bitmap( SCREEN_WIDTH, SCREEN_HEIGHT);
#endif // USE_ALLEGRO

    setupGame();

////TODO: How to read keys from keyboard in NIOS2??
    while( 1 ){
    	refresh_kb();
        p1Move();
        p2Move();
        drawScore();
        if (p1_moved || p2_moved){
        	max_delay = 7500;
        }else {
        	max_delay = 10000;
        }
        for (delay = 0; delay < max_delay; delay ++);
        moveBall();
        /*if (delay == 10){
        	moveBall();
        	delay = 0;
        }else{
        	delay++;
        }
		*/

        checkWin();
    }
    return 0;
}
#ifdef USE_ALLEGRO
END_OF_MAIN();
#endif

