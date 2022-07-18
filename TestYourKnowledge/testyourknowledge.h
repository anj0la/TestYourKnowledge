#ifndef testyourknowledge
#define testyourknowledge
#include "allegro.h"

// Global variable declarations

extern int question_index;
extern int option_index;
extern int num_of_files;

// Constant variables

#define MAX_NUM_QUESTIONS 220
#define MAX_NUM_OPTIONS 4
#define MAX_LINES 60
#define MAX_CONTENTS 880
#define MAX_NUM_FILES 22

// Sound variables

int volume = 32;
int panning = 32;
int frequency = 1000;

// Other variables

char lines[MAX_LINES][256];
char file_contents[MAX_CONTENTS][256];
char num_files[MAX_NUM_FILES][256];

// Quiz struct

struct Quiz {
	const char* questions[MAX_NUM_QUESTIONS];
	const char* options[MAX_NUM_QUESTIONS][MAX_NUM_OPTIONS];
	const char* answers[MAX_NUM_QUESTIONS];
	int question_order[MAX_NUM_QUESTIONS];
	int num_questions;
} quiz;

#endif 
