#ifndef screens
#define screens
#include "allegro.h"

// Global variable declarations

extern int selection;
extern int max_selection;

// Constant variables

#define WIDTH 800
#define HEIGHT 600
#define MAX_NUM_QUESTIONS 220
#define MAX_NUM_OPTIONS 4
#define MAX_NUM_QUIZ_QUESTIONS 100
#define LT_PURPLE makecol(207, 159, 255)
#define WHITE makecol(255, 255, 255)
#define LT_CORAL makecol(250, 224, 207)
#define INIT_X1_BAR 260
#define INIT_X2_BAR 540
#define INIT_Y1_BAR 250
#define INIT_Y2_BAR 300
#define UNIT_X1_BAR (INIT_X1_BAR - 100)
#define UNIT_X2_BAR (INIT_X2_BAR - 180)
#define CHAPTER_X1_BAR (INIT_X1_BAR - 200)
#define CHAPTER_X2_BAR (INIT_X2_BAR - 290)
#define CHAPTER_Y1_BAR (INIT_Y1_BAR - 10)
#define CHAPTER_Y2_BAR (INIT_Y2_BAR - 30)

// Graphics, sound and font variables

SAMPLE* background_music;
SAMPLE* correct_ding;
SAMPLE* wrong_buzzer;
BITMAP* background;
BITMAP* buffer;
BITMAP* correct;
BITMAP* wrong;
FONT* font_header;
FONT* font_subheader;
FONT* font_body;

int choose_quiz_mode();
void draw_choose_quiz_mode_screen();
void draw_choose_unit_mode_screen();
void draw_choose_chapter_mode_screen();
void draw_welcome_screen();
void draw_game_screen(char* score_char, char* total_questions);
void draw_question(const char* question, const char* option1, const char* option2, const char* option3, const char* option4);
void display_correct();
void display_wrong(char correct_answer);
void highlight_selected_answer(char selected_answer);
void end_game();

#endif // !screens
