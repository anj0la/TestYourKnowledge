#include "screens.h"
#include <allegro.h>

// Global variables 

int selection = 1;
int max_selection = 3;

/*
Chooses the quiz mode of the user, whether it is the full text, a particular unit, or a particular chapter.
@return - 1 if a mode was successfully chosen (pressed the ENTER key), 0 if the ESC key was pressed to quit the game; otherwise, -1 if an invalid key was selected.
*/
int choose_quiz_mode() {
	if (key[KEY_ESC]) {
		return 0;
	}
	else {
		if (key[KEY_UP] && selection != 1) {
			selection--;
			key[KEY_UP] = 0;
			return 2; 
		}
		else if (key[KEY_DOWN] && selection != max_selection) {
			selection++;
			key[KEY_DOWN] = 0;
			return 2;
		}
		else if (key[KEY_ENTER]) {
			return 1;
		}
	}
	return -1;
}

/*
Draws and displays the choose quiz mode screen.
*/
void draw_choose_quiz_mode_screen() {
	// Clearing buffer and blitting the background to the buffer
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, 800, 600);
	// Setting the selection bar to the correct position
	rectfill(buffer, INIT_X1_BAR, INIT_Y1_BAR + ((selection - 1) * 80), INIT_X2_BAR, INIT_Y2_BAR + ((selection - 1) * 80), LT_CORAL);
	// Adding text to the buffer
	textout_centre_ex(buffer, font_header, "Choose what the quiz will be on!", SCREEN_W / 2, 140, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "Use the up and down arrow keys to select an option,", SCREEN_W / 2, 180, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "then the ENTER key after selecting your option to continue!", SCREEN_W / 2, 200, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, "1. THE ENTIRE TEXT", SCREEN_W / 2, 260, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, "2. A UNIT", SCREEN_W / 2, 340, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, "3. A CHAPTER", SCREEN_W / 2, 420, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

/*
Draws and displays the choose unit mode screen.
*/
void draw_choose_unit_mode_screen() {
	// Clearing buffer and blitting the background to the buffer
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, 800, 600);
	// Setting the selection bar to the correct position
	if (selection > 4) {
		rectfill(buffer, (UNIT_X1_BAR) * 2.55, INIT_Y1_BAR + ((selection - 5) * 60), (UNIT_X2_BAR) * 1.72, INIT_Y2_BAR + ((selection - 5) * 60), LT_CORAL);
	}
	else {
		rectfill(buffer, UNIT_X1_BAR, INIT_Y1_BAR + ((selection - 1) * 60), UNIT_X2_BAR, INIT_Y2_BAR + ((selection - 1) * 60), LT_CORAL);
	}
	// Adding text to the buffer
	textout_centre_ex(buffer, font_header, "Choose what unit the quiz will be on!", SCREEN_W / 2, 140, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "Use the up and down arrow keys to select an option,", SCREEN_W / 2, 180, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "then the ENTER key after selecting your option to continue!", SCREEN_W / 2, 200, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "1. UNIT 1", SCREEN_W / 4, 260, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "2. UNIT 2", SCREEN_W / 4, 320, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "3. UNIT 3", SCREEN_W / 4, 380, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "4. UNIT 4", SCREEN_W / 4, 440, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "5. UNIT 5", SCREEN_W / 2 + 50, 260, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "6. UNIT 6", SCREEN_W / 2 + 50, 320, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "7. UNIT 7", SCREEN_W / 2 + 50, 380, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "8. UNIT 8", SCREEN_W / 2 + 50, 440, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

/*
Draws and displays the choose chapter mode screen.
*/
void draw_choose_chapter_mode_screen() {
	// Clearing buffer and blitting the background to the buffer
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, 800, 600);
	// Setting the selection bar to the correct position
	if (selection > 7 && selection <= 14) {
		rectfill(buffer, CHAPTER_X1_BAR * 4.75, CHAPTER_Y1_BAR + ((selection - 8) * 40), CHAPTER_X2_BAR * 1.95, CHAPTER_Y2_BAR + ((selection - 8) * 40), LT_CORAL);
	}
	else if (selection > 14) {
		rectfill(buffer, CHAPTER_X1_BAR * 8.5, CHAPTER_Y1_BAR + ((selection - 15) * 40), CHAPTER_X2_BAR * 2.91, CHAPTER_Y2_BAR + ((selection - 15) * 40), LT_CORAL);
	}
	else {
		rectfill(buffer, CHAPTER_X1_BAR, CHAPTER_Y1_BAR + ((selection - 1) * 40), CHAPTER_X2_BAR, CHAPTER_Y2_BAR + ((selection - 1) * 40), LT_CORAL);
	}
	// Adding text to the buffer
	textout_centre_ex(buffer, font_header, "Choose what chapter the quiz will be on!", SCREEN_W / 2, 140, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "Use the up and down arrow keys to select an option,", SCREEN_W / 2, 180, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "then the ENTER key after selecting your option to continue!", SCREEN_W / 2, 200, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "1. CHAPTER 1", SCREEN_W / 4 - 125, 240, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "2. CHAPTER 2", SCREEN_W / 4 - 125, 280, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "3. CHAPTER 3", SCREEN_W / 4 - 125, 320, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "4. CHAPTER 4", SCREEN_W / 4 - 125, 360, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "5. CHAPTER 5", SCREEN_W / 4 - 125, 400, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "6. CHAPTER 6", SCREEN_W / 4 - 125, 440, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "7. CHAPTER 7", SCREEN_W / 4 - 125, 480, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "8. CHAPTER 8", SCREEN_W / 4 + 100, 240, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "9. CHAPTER 9", SCREEN_W / 4 + 100, 280, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "10. CHAPTER 10", SCREEN_W / 4 + 100, 320, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "11. CHAPTER 11", SCREEN_W / 4 + 100, 360, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "12. CHAPTER 12", SCREEN_W / 4 + 100, 400, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "13. CHAPTER 13", SCREEN_W / 4 + 100, 440, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "14. CHAPTER 14", SCREEN_W / 4 + 100, 480, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "15. CHAPTER 15", SCREEN_W / 2 + 125, 240, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "16. CHAPTER 16", SCREEN_W / 2 + 125, 280, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "17. CHAPTER 17", SCREEN_W / 2 + 125, 320, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "18. CHAPTER 18", SCREEN_W / 2 + 125, 360, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "19. CHAPTER 19", SCREEN_W / 2 + 125, 400, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "20. CHAPTER 20", SCREEN_W / 2 + 125, 440, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "21. CHAPTER 21", SCREEN_W / 2 + 125, 480, LT_PURPLE, -1);
	textout_ex(buffer, font_header, "22. CHAPTER 22", SCREEN_W / 2 + 125, 520, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

/*
Draws and displays the welcome screen.
*/
void draw_welcome_screen() {
	blit(background, buffer, 0, 0, 0, 0, 800, 600);
	textout_centre_ex(buffer, font_header, "A game based on Pocket Triva, a simple quiz game!", SCREEN_W / 2, 140, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "This game tests your knowledge on the Game Programming All in One textbook!", SCREEN_W / 2, 230, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "You can choose to be quizzed on the entire text, a particular unit or chapter!", SCREEN_W / 2, 270, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, "Use the A, B, C and D keys to select your answer for each question!", SCREEN_W / 2, 310, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_subheader, "Ready to test your knowledge? Press the ENTER key to begin!", SCREEN_W / 2, 390, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

/*
Draws and displays the game screen.
*/
void draw_game_screen(char* score_char, char* total_questions) {
	// Clearing buffer and blitting the background to the buffer
	clear_bitmap(buffer);
	blit(background, buffer, 0, 0, 0, 0, 800, 600);
	// Adding text to the buffer
	textout_ex(buffer, font_subheader, "Score:", 10, SCREEN_H - 30, LT_PURPLE, -1);
	textout_ex(buffer, font_subheader, score_char, 75, SCREEN_H - 30, LT_PURPLE, -1);
	textout_ex(buffer, font_subheader, "/", 110, SCREEN_H - 30, LT_PURPLE, -1);
	textout_ex(buffer, font_subheader, total_questions, 125, SCREEN_H - 30, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

void draw_question(const char* question, const char* option1, const char* option2, const char* option3, const char* option4) {
	char optionA[128] = "A. ";
	char optionB[128] = "B. ";
	char optionC[128] = "C. ";
	char optionD[128] = "D. ";
	strcat(optionA, option1);
	strcat(optionB, option2);
	strcat(optionC, option3);
	strcat(optionD, option4);
	textout_centre_ex(buffer, font_header, "Question!", SCREEN_W / 2, 140, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_body, question, SCREEN_W / 2, 180, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, optionA, SCREEN_W / 2, 240, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, optionB, SCREEN_W / 2, 290, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, optionC, SCREEN_W / 2, 340, LT_PURPLE, -1);
	textout_centre_ex(buffer, font_header, optionD, SCREEN_W / 2, 390, LT_PURPLE, -1);
	// Updating the screen
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

void display_correct() {
	blit(correct, buffer, 0, 0, 300, 500, 200, 50);
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

void display_wrong() {
	blit(wrong, buffer, 0, 0, 300, 500, 200, 50);
	acquire_screen();
	blit(buffer, screen, 0, 0, 0, 0, 800, 600);
	release_screen();
}

/*
Destroys the objects used in the game, and exits the application.
*/
void end_game() {
	destroy_sample(background_music);
	destroy_sample(correct_ding);
	destroy_sample(wrong_buzzer);
	destroy_bitmap(background);
	destroy_bitmap(buffer);
	destroy_bitmap(correct);
	destroy_bitmap(wrong);
	destroy_font(font_header);
	destroy_font(font_subheader);
	destroy_font(font_body);
	remove_sound();
	allegro_exit();
}
