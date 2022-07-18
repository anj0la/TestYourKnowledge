#include "testyourknowledge.h"
#include "screens.h"
#include <allegro.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

//////////////////////
// Question Logic
//////////////////////

int file_contents_index = 0;
int question_index = 0;
int option_index = 0;

/*
Parses a file filled with 10 questions.
*/
void parse_question(const char* filename) {
	FILE* file;
	file = fopen(filename, "r");
	int i = 0;
	if (file != NULL) {
		// The file was successfully opened
		printf("Success");
		while (i < MAX_LINES && fgets(lines[i], sizeof(lines[0]), file)) {
			lines[i][strlen(lines[i]) - 1] = '\0';
			strcpy(file_contents[file_contents_index], lines[i]);
			file_contents_index++;
		}
		fclose(file);
	}
	else {
		// An error has occurred and the game closes
		exit(0);
	}
}

/*
Generates all questions by parsing each individual chapter file corresponding with the number of files needed to parse through.
*/
void generate_all_questions(int num_of_files) {
	for (int i = 1; i <= num_of_files; i++) {
		parse_question(num_files[i]);
	}
	quiz.num_questions = num_of_files * 10;
}

/*
Creates the quiz, by copying the contents of the file contents array into the quiz questions, options and answers arrays.
*/
void create_quiz() {
	for (int i = 0; i < file_contents_index; i++) {
		if (i % 6 == 0) {
			quiz.questions[question_index] = file_contents[i];
		}
		else if (i % 6 == 5) {
			quiz.answers[question_index] = file_contents[i];
			option_index = 0;
			question_index++;
		}
		else {
			quiz.options[question_index][option_index] = file_contents[i];
			option_index++;
		}
	}
}

/*
Randomizes the question order.
*/
void randomize_question_order() {
	// Initializing question order array
	for (int i = 0; i < quiz.num_questions; i++) {
		quiz.question_order[i] = i;
	}
	// Shuffling question order
	for (int i = 0; i < quiz.num_questions; i++) {
		int random = rand() % quiz.num_questions;
		int temp = quiz.question_order[random];
		quiz.question_order[random] = quiz.question_order[i];
		quiz.question_order[i] = temp;
	}
}
/*
Opens an option file containing the path names of the questions to be parsed from.
@param filename - the path of the file to be opened
*/
void open_option_file(const char* filename) {
	FILE* file;
	file = fopen(filename, "r");
	int i = 0;
	if (file != NULL) {
		// The file was successfully opened
		while (i < MAX_NUM_FILES && fgets(num_files[i], sizeof(num_files[0]), file)) {
			num_files[i][strlen(num_files[i]) - 1] = '\0';
			i++;
		}
		fclose(file);
	}
	else {
		// An error has occurred and the game closes
		end_game();
		exit(0);
	}
}

/*
Generates the quiz for the game, depending on the option file (only for full text and units,
as chapters are handled differently).
@param option_file_name - the name of the option file to be opened and read from
*/
void generate_quiz(const char* option_filename) {
	open_option_file(option_filename);
	int num_of_files = atoi(num_files[0]);
	generate_all_questions(num_of_files);
	create_quiz();
	randomize_question_order();
}

/*
* Generates the quiz for the game, depending on the chapter chosen in the choose chapter mode section.
* @param filename - the filename of the selected chapter
*/
void generate_quiz_from_chapter(const char* filename) {
	parse_question(filename);
	quiz.num_questions = 10;
	create_quiz();
	randomize_question_order();
}

//////////////////////
// Game Logic
//////////////////////

/*
Returns 1 (success) if the ENTER key was pressed, or 0 if the ESC key was pressed. 
Any other key pressed will do nothing, either the ENTER key or ESC key must be pressed
for the game to respond accordingly.
*/
int handle_beginning_keypress() {
	while (1) {
		if (key[KEY_ENTER]) {
			return 1;
		}
		else if (key[KEY_ESC]) {
			return 0;
		}
	}
}

int handle_choose_quiz_option() {
	while (1) {
		int mode_chosen = choose_quiz_mode();
		if (mode_chosen == 0) {
			return 0;
		}
		else if (mode_chosen == 1) {
			return 1;
		}
		else if (mode_chosen == 2) {
			draw_choose_quiz_mode_screen();
		}
	}
}

int handle_choose_unit_option() {
	while (1) {
		int mode_chosen = choose_quiz_mode();
		if (mode_chosen == 0) {
			return 0;
		}
		else if (mode_chosen == 1) {
			return 1;
		}
		else if (mode_chosen == 2) {
			draw_choose_unit_mode_screen();
		}
	}
}

int handle_choose_chapter_option() {
	while (1) {
		int mode_chosen = choose_quiz_mode();
		if (mode_chosen == 0) {
			return 0;
		}
		else if (mode_chosen == 1) {
			return 1;
		}
		else if (mode_chosen == 2) {
			draw_choose_chapter_mode_screen();
		}
	}
}


int get_game_input() {
	if (key[KEY_ESC]) {
		return 'q';
	}
	else {
		if (key[KEY_A]) {
			return 'a';
		}
		else if (key[KEY_B]) {
			return 'b';
		}
		else if (key[KEY_C]) {
			return 'c';
		}
		else if (key[KEY_D]) {
			return 'd';
		}
		else {
			return 'f';
		}
	}
}

int handle_game_input() {
	while (1) {
		int result = get_game_input();
		if (result != 'f') {
			return result;
		}
	}
}

/*
Checks if the selection variable is either 2 or 3, and if so, resets the selection and max_selection
variables accordingly and returns 1 or 2. Otherwise, -1 is return to indicate that the selection
chosen was the full text.
*/
int check_selected_quiz_option() {
	if (selection == 2) {
		// Resetting selection and changing max_selection
		selection = 1;
		max_selection = 8;
		//draw_choose_unit_mode_screen();
		return 1;
	}
	else if (selection == 3) {
		// resetting selection and changing max_selection
		selection = 1;
		max_selection = 22;
		//draw_choose_chapter_mode_screen();
		return 2;
	}
	return -1;
}

int main(void) {
	srand(time(NULL));
	// Initializing Allegro, keyboard and sound
	if (allegro_init() != 0) {
		return 1;
	}
	set_color_depth(24);
	install_keyboard();
	set_keyboard_rate(10000, 0);
	int ret = set_gfx_mode(GFX_SAFE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message("Error setting GFX mode.");
		return 1;
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
		return 1;
	}

	// Loading music and sounds
	background_music = load_sample("background_music.wav");
	correct_ding = load_sample("answer_correct.wav");
	wrong_buzzer = load_sample("answer_wrong.wav");
	if (!background_music || !correct_ding || !wrong_buzzer) {
		allegro_message("Error reading WAV file.");
		return 1;
	}

	// Loading bmp files
	background = load_bitmap("game_background_24.bmp", NULL);
	correct = load_bitmap("correct_box_24.bmp", NULL);
	wrong = load_bitmap("incorrect_box_24.bmp", NULL);
	if (!background || !correct || !wrong) {
		allegro_message("Error loading bitmaps.");
		return 1;
	}

	// Loading fonts
	font_header = load_font("font_header.pcx", NULL, NULL);
	font_subheader = load_font("font_subheader.pcx", NULL, NULL);
	font_body = load_font("font_body.pcx", NULL, NULL);
	if (!font_header || !font_subheader || !font_body) {
		allegro_message("Error loading fonts.");
		return 1;
	}
	// Creating secondary buffer
	buffer = create_bitmap(SCREEN_W, SCREEN_H);

	// Playing the background music (loop)
	play_sample(background_music, volume, panning, frequency, TRUE);
	draw_welcome_screen();

	int enter_key_pressed = handle_beginning_keypress();
	if (enter_key_pressed == 0) {
		end_game();
		return 0;
	} 
	else {
		key[KEY_ENTER] = 0; // sets the ENTER key pressed value back to false
	}

	// Handling choose quiz option
	draw_choose_quiz_mode_screen();
	int mode = handle_choose_quiz_option();
	if (mode == 0) {
		end_game();
		return 0;
	} 
	else {
		key[KEY_ENTER] = 0; 
	}

	// Checking selection
	int selected_mode = check_selected_quiz_option();
	if (selected_mode == 1) {
		draw_choose_unit_mode_screen();
		int unit_mode = handle_choose_unit_option();
		if (unit_mode == 0) {
			end_game();
			return 0;
		}
		else {
			char file_path[256];
			sprintf_s(file_path, 256, "unit%d.txt", selection);
			generate_quiz(file_path);
		}
	} 
	else if (selected_mode == 2) {
		draw_choose_chapter_mode_screen();
		int chapter_mode = handle_choose_chapter_option();
		if (chapter_mode == 0) {
			end_game();
			return 0;
		}
		else {
			char file_path[256];
			sprintf_s(file_path, 256, "chapter%d.txt", selection);
			generate_quiz_from_chapter(file_path);
		}
	}
	else { // selection = -1, generate quiz based on entire text
		generate_quiz("allchapters.txt");
	}
	// Initializing game variables
	int score = 0;
	int question_tracker = 0;
	char score_char[3];
	char total_questions[3];
	
	sprintf(score_char, "%d", score);
	sprintf(total_questions, "%d", quiz.num_questions);
	draw_game_screen(score_char, total_questions);
	int question_order = quiz.question_order[0];
	draw_question(quiz.questions[question_order], quiz.options[question_order][0], quiz.options[question_order][1],
		quiz.options[question_order][2], quiz.options[question_order][3]);
	char correct_answer = quiz.answers[question_order][0];
	int answer = handle_game_input();
	if (answer == 'q') {
		end_game();
		exit(0);
	}
	if (answer == correct_answer) {
		play_sample(correct_ding, volume, panning, frequency, FALSE);
		display_correct();
		score++;
	}
	else {
		play_sample(wrong_buzzer, volume, panning, frequency, FALSE);
		display_wrong();
	}

	// Game loop
	/*for (int i = 0; i < quiz.num_questions; i++) {
		draw_game_screen(score_char, total_questions);
		int question_order = quiz.question_order[i];
		draw_question(quiz.questions[question_order], quiz.options[question_order][0], quiz.options[question_order][1],
			quiz.options[question_order][2], quiz.options[question_order][3]);
		char answer = handle_game_input();
		if (answer == "q") {
			end_game();
			exit(0);
		}
		if (answer == quiz.answers[question_order]) {
			play_sample(correct_ding, volume, panning, frequency, FALSE);
			display_correct();
			score++;
		}
		else {
			play_sample(wrong_buzzer, volume, panning, frequency, FALSE);
			display_wrong();
		}
	}*/
	
	



	// play_sample(correct_ding, volume, panning, frequency, FALSE);
	// play_sample(wrong_buzzer, volume, panning, frequency, FALSE);

	while (!key[KEY_ESC]);
	end_game();
	return 0;
}
END_OF_MAIN()