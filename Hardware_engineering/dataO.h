/*header file to get all necessary functions into code */

#include <stdint.h>
/*buffer array*/
uint8_t bufferArray[2][512];


/*arrays for render*/
extern const uint8_t const player[8];

extern const uint8_t const charArray[50];
extern const uint8_t const gameover[2][512];
extern const uint8_t const title_Screen[3][512];
extern const uint8_t const score_Screens[2][512];
extern const uint8_t const score_Main[3][512];
extern const uint8_t const allMaps[4][512];


/*necessary initialization functions */

void begin_main (void);
void enable_interrupt(void);


void timer1_begin (void);
void timer1_stop (void);

void game_over(int toggle);

int SinglePlayer;
int screenChanger;

/* display functions */
void display_init(void);
void display_update(int toggle);
void clearDisplay(int toggle);
void drawPixel(int toggle, int x, int y);

void updateBuffer(int toggle);
char * itoaconv( int num );

/*buttons functions */
int getbtnsP1(void);
int movement(int timeout);
void startBullet(void);
void flyingBullet(void);

/*graphics */

void renderPlayer (int toggle, int x, int y, int cape, int direction);
void renderPlayer2 (int toggle, int x, int y, int steps, int direction);

void displayString(int toggle, int x, int line, char* string);
void renderTextures(int toggle);

void changeCape(void);
void changeSteps(void);

int bullet2(int timeout);

void renderBullet (int toggle, int x, int y, int direction);

int wallLShapeX1;
int wallLShapeY1;
int wallTShapeX1;
int wallTShapeY1;
int wallCShapeX1;
int wallCShapeY1;
int wallLShapeX2;
int wallLShapeY2;
int wallTShapeX2;
int wallTShapeY2;
int wallCShapeX2;
int wallCShapeY2;

int maps;
int bulletclear;
int toggle;

int w;

int titleShifter;

int player1kills;
int player2kills;

int botkills;

//interrupt
void user_isr(void);
void quicksleep(int cyc);

void Win(void);

unsigned int seed(void);
