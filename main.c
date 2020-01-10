#include "battleship.h"

int main(int argc, char *argv[]) {
    int state = 0;
    int start = 0;
    char c;
    char New_Game[]="*New Game";
    char Resume[]=" Resume Game";
    char Quit[]=" Quit";
    char *jucator[13];
    char comp[20][20];
    char comp_aux[12][22];
    int ncols;
    int comp_score = 0;
    int jucator_score = 0;

    FILE * fp;
    if ( argc == 1 ){
        fprintf(stderr, "[Eroare]: Nu s-au dat argumente de comanda\n");
    return 1;
    }
    else{
        for (int i = 1; i < argc; i++ ){
            if ( (fp = fopen(argv[i], "r")) == NULL ){
                fprintf( stderr, "[Eroare]: Fisierul %s nu poate fi deschis.\n", argv[i]);
                return 1;
            }
            fclose(fp);  
        }
    }

    WINDOW *menu = initscr(); 
    clear();
    noecho();
    cbreak(); 
    curs_set(0);
    refresh();
    start_color();

    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    bkgd(COLOR_PAIR(2));

    do {
		clear();
		ncols = getmaxx(menu);
		wattron(menu, COLOR_PAIR(4));
		mvwprintw(menu, 1, 38, " _           _   _   _           _     _ ");      
		mvwprintw(menu, 2, 38, "| |         | | | | | |         | |   (_)      ");
		mvwprintw(menu, 3, 38, "| |__   __ _| |_| |_| | ___  ___| |__  _ _ __  ");
		mvwprintw(menu, 4, 38, "| '_ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ ");
		mvwprintw(menu, 5, 38, "| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |");
		mvwprintw(menu, 6, 38, "|_.__/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ ");
		mvwprintw(menu, 7, 38, "                                        | |    ");
		mvwprintw(menu, 8, 38, "                                        |_| ");
		wattron(menu, COLOR_PAIR(2));
		mvwprintw(menu, 9, 30, "                   __  o");
		mvwprintw(menu, 10, 30, "                  __  o");
		mvwprintw(menu, 11, 30, "                 /  |/");
		mvwprintw(menu, 12, 30, "               _/___|___________");
		mvwprintw(menu, 13, 30, "              /  _______      __\\");
		mvwprintw(menu, 14, 30, "_______                        /  /_o_||__|    |");
		mvwprintw(menu, 15, 30, " '\\'_'\\'_'\\'_'\\'______________________/___           |");
		mvwprintw(menu, 16, 30, "  '\\'                       '\\'____________|___________");
		mvwprintw(menu, 17, 30, "   '\\'     ||                                        |");
		mvwprintw(menu, 18, 30, "    '\\' +_||_+       () () ()                   ____|");
		mvwprintw(menu, 19, 30, "     '\\'                                          |");
		mvwprintw(menu, 20, 30, "    '\\'    _  ,,          _                   /");
		mvwprintw(menu, 21, 30, " ^^^^^^^^^^^^^^^^ '\\'_.= )  -._____,' ;__________ /_^^^^^^^^");
		mvwprintw(menu, 22, 30, "  ^^^^  ^^^^                                        '\\'__|==% ^^");
		mvwprintw(menu, 23, 30, " ^^         ^^^^^^^^       ^^^^ ^^^ ^^^^^   ^^^^^^^^ ^      ^^^^");
		mvwprintw(menu, 24, 30, "^^^   ^^^^          ^^^^^^^^^^^^          ^^^^     ^^     ^^^^^");
		wattron(menu, COLOR_PAIR(2));
		box(menu, 0, 0);
		state = main_menu(c, New_Game, Resume, Quit, state);
		wattron(menu, COLOR_PAIR(1));
		mvaddstr(26, ncols / 2 - 4, New_Game);
		wattron(menu, COLOR_PAIR(2));
		mvaddstr(27, ncols / 2 - 4, Resume);
		wattron(menu, COLOR_PAIR(3));
		mvaddstr(28, ncols / 2 - 4, Quit);
		wattron(menu, COLOR_PAIR(4));
		mvaddstr(31, 2, "To navigate through the menu use Key_UP and Key_DOWN, to select an item press ENTER");
		wattron(menu, COLOR_PAIR(2));
		refresh();
		c = getchar();
		if (c == 13) {
		    if (state == 0) {
		        new_game(argc, argv, jucator, comp, comp_aux, &comp_score, &jucator_score);
		        start = 1;
		    } 
		    else if (state == 1) {
			    if(start) {
			        resume(jucator, comp, comp_aux, &comp_score, &jucator_score);
			    }
		    } else {
		        endwin();
		        exit(0);
		    }
		}
    }
    while(1);
    for(int i = 0; i < 12; i++)
        free(jucator[i]);
    pclose(fp);
    return 0;
}