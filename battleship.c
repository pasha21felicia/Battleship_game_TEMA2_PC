#include "battleship.h"

//citeste tabelul jucatorului din fisier
void read(char **line, char *nume)
{
    char tmp[100];
    FILE * pFile;
    pFile = fopen(nume, "r");
    for (int i = 0 ;i < 12; i++){
        fgets(tmp, 100, pFile);
        line[i] = (char*) malloc( strlen(tmp) * sizeof(char) + 1 );
        strcpy(line[i], tmp);
    }
}

//genereaza un numar random intre 2 limite
int getRandoms(int lower, int upper) 
{ 
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
} 

//contruieste meniul principal
int main_menu(char c, char New_Game[], char Resume[], char Quit[], int state) {
    keypad(stdscr, TRUE);
    if (c == K_DOWN && state < 2) {
        state++;
    }
    if (c == K_UP && state > 0) {
        state--;
    }
    switch (state) {
        case 0: {
            New_Game[0]='*';
            Resume[0]=' ';
            Quit[0]=' ';
            break;
        }
        case 1: {
            New_Game[0]=' ';
            Resume[0]='*';
            Quit[0]=' ';
            break;
        }
        case 2: {
            New_Game[0]=' ';
            Resume[0]=' ';
            Quit[0]='*';
            break;
        }
        default: {
            break;
        }
    }
    return state;
}

//creeaza un joc nou, cu tabele dinnou generate
void new_game(int argc, char *argv[], char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score) {
    create_boards(argc, argv, jucator, comp, comp_aux);
    game(jucator, comp, comp_aux, comp_score, jucator_score);
} 

//restabileste vechiul joc
void resume( char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score) {
    game(jucator, comp, comp_aux, comp_score, jucator_score);
}

//verifica in sus nr de celule goale
int checkNORTH(int ship_lenth, int row, int col, char comp[20][20]){

    int free_col = 0 ;
    for (int i = row - 1; i >= 0; --i){
        if (comp[i][col] == '@' && ( comp[i+1][col] != 'x' || comp[i+1][col] != '.'))
        free_col++;
        else break;
    }
    return free_col;

} 

//verifica in jos nr de celule goale
int checkSOUTH(int ship_lenth, int row, int col, char comp[20][20]){

    int free_col = 0 ;
    for (int i = row + 1; i < 10; i++){
        if (comp[i][col] == '@' && (comp[i+1][col] != 'x' || comp[i+1][col] != '.'))
            free_col++;
        else break;
    }
    return free_col;

} 

//verifica la dreapta nr de celule goale
int checkEAST(int ship_lenth, int row, int col, char comp[20][20]){

    int free_col = 0 ;
    for (int i = col + 1; i < 10; i++){
        if (comp[row][i] == '@' && (comp[row][i+1] != 'x' || comp[row][i+1] != '.') )
            free_col++;
        else break;
    }
    return free_col;

}

//verifica la stanga nr de celule goale
int checkWEST(int ship_lenth, int row, int col, char comp[20][20]){

    int free_col = 0 ;
    for (int i = col - 1; i >= 0; --i){
        if (comp[row][i] == '@' && (comp[row][i+1] != 'x' || comp[row][i+1] != '.')) 
            free_col++;
        else break;
    }

    return free_col;

}

//plaseaza de ship_length ori 'x' in sus
void placeNORTH(int ship_length, int row, int col, char comp[20][20]){
    int pos  = row - ship_length;
    comp[pos - 1][col - 1] = '.';
    comp[pos - 1][col] = '.';
    comp[pos - 1][col + 1] = '.';

    for (int i = pos; i <= row ; i++){
        comp[i][col] = 'x';
        comp[i][col - 1] = '.';
        comp[i][col + 1] = '.';
    }
    comp[row + 1][col - 1] = '.';
    comp[row + 1][col] = '.';
    comp[row + 1][col + 1] = '.';

}

//plaseaza de ship_length ori 'x' in jos
//pun in jurul pozitiei cu 'x' pe '.' pentru a marca 
//distanta valida intre nave
void placeSOUTH(int ship_length, int row, int col, char comp[20][20]){
    int pos = row + ship_length;
    comp[row - 1][col] = '.';
    comp[row - 1][col - 1] = '.';
    comp[row - 1][col + 1] = '.';

    for (int i = row; i <= pos ; i++){
    comp[i][col] = 'x';
    comp[i][col - 1] = '.';
    comp[i][col + 1] = '.';
    }

    comp[pos + 1][col] = '.';
    comp[pos + 1][col - 1] = '.';
    comp[pos + 1][col + 1] ='.';

}

//plaseaza de ship_length ori 'x' in dreapta
void placeEAST(int ship_length, int row, int col, char comp[20][20]){
    int pos = col + ship_length;
    comp[row - 1][col -1] = '.';
    comp[row][col - 1] = '.';
    comp[row + 1][col - 1] = '.';

    for (int i = col ; i <=pos; i++){
    comp[row][i] = 'x';
    comp[row - 1][i] = '.';
    comp[row + 1][i] = '.';

    }
    comp[row][pos + 1] = '.';
    comp[row - 1][pos + 1] = '.';
    comp[row + 1][pos + 1] ='.';

}

//plaseaza de ship_length ori 'x' in stanga
void placeWEST(int ship_length, int row, int col, char comp[20][20]){
    int pos = col - ship_length;
    comp[row - 1][pos - 1] = '.';
    comp[row][pos - 1] = '.';
    comp[row + 1][pos - 1] = '.';

    for (int i = pos ; i <= col; i++){
        comp[row][i] = 'x';
        comp[row - 1][i] = '.';
        comp[row + 1][i] = '.';
    }
    comp[row - 1][col + 1] = '.';
    comp[row][col + 1] = '.';
    comp[row + 1][col + 1] = '.';

}

//creeaza tabelul calcatorului si al jucatorului
void create_boards(int argc, char *argv[], char **jucator, char comp[20][20], char comp_aux[12][22]) {
    srand(time(0)); 
    char nume[100];
    int num = getRandoms(1, argc - 1);
    strcpy(nume, argv[num]);
    bkgd(COLOR_PAIR(4));
    clear();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    refresh();
    
    //generez o coloana si un rand
    int free_col;
    int row = getRandoms(0, 9);
    int col = getRandoms(0, 9);
    int direction;
    //umplu matricea comp cu caracterul @
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            comp[i][j] = '@';
        }
    }

    //generez directia in care plasez nava de 4
    //daca directia e valida
    //plasez nava in directia aia
    do{
        direction = getRandoms(0, 3);
        if (direction == NORTH){
            free_col = checkNORTH(3, row, col ,comp); 
            if(free_col >= 3) {
                placeNORTH(3, row, col, comp);
                break;
            }
        }
        if (direction == SOUTH){
            free_col = checkSOUTH(3, row, col ,comp);
            if(free_col >= 3) {
                placeSOUTH(3, row, col, comp);
                break;  
            }
        }
        if (direction == EAST){
            free_col = checkEAST(3, row, col ,comp);
            if(free_col >= 3){
                placeEAST(3, row, col, comp);
                break;
            }
        }
        if (direction == WEST){
            free_col = checkWEST(3, row, col ,comp);
            if(free_col >= 3){
                placeWEST(3, row, col, comp);
                break;
            }
        }
       
    }while(free_col < 3);
  
    //acelasi principiu, plasez nava de 3
    for(int i = 0; i < 2; i++){
        do{

            row = getRandoms(0, 9);
            col = getRandoms(0, 9);
            direction = getRandoms(0, 3);
            if (direction == NORTH){
                free_col = checkNORTH(2, row, col ,comp);
                if(free_col >= 2 && comp[row][col] != 'x' && comp[row][col] != '.') {
                  placeNORTH(2, row, col, comp);
                  break;
                }
            }
            if (direction == SOUTH){
                free_col = checkSOUTH(2, row, col, comp);
                if(free_col >= 2 && comp[row][col] != 'x' && comp[row][col] != '.') {
                    placeSOUTH(2, row, col, comp);
                    break;  
                }   
            }
            if (direction == EAST){
                free_col = checkEAST(2, row, col, comp);
                if(free_col >= 2 && comp[row][col] != 'x' && comp[row][col] != '.'){
                    placeEAST(2, row, col, comp);
                    break;
                }
            }
            if (direction == WEST){
                free_col = checkWEST(2,row, col, comp);
                if(free_col >= 2 && comp[row][col] != 'x' && comp[row][col] != '.'){
                    placeWEST(2, row, col, comp);
                    break;
                }
            }
            
        }while(comp[row][col] == 'x' || comp[row][col] == '.' || free_col < 2);
      
    }
  
    //plasez nava de 2
    for(int i = 0; i < 3; i++){
        do{
            row = getRandoms(0, 9);
            col = getRandoms(0, 9);
            direction = getRandoms(0, 3);
            if (direction == NORTH){
                free_col = checkNORTH(1, row, col ,comp);
                if(free_col >= 1 && comp[row][col] != 'x' && comp[row][col] != '.') {
                placeNORTH(1, row, col, comp);
                break;
                }
            }
            if (direction == SOUTH){
                free_col = checkSOUTH(1, row, col, comp);
                if(free_col >= 1 && comp[row][col] != 'x' && comp[row][col] != '.') {
                    placeSOUTH(1, row, col, comp);
                    break;  
                }
            }
            if (direction == EAST){
                free_col = checkEAST(1,row, col, comp);
                if(free_col >= 1 && comp[row][col] != 'x' && comp[row][col] != '.'){
                    placeEAST(1, row, col, comp);
                    break;
                }
            }
            if (direction == WEST){
                free_col = checkWEST(1, row, col, comp);
                if(free_col >= 1 && comp[row][col] != 'x' && comp[row][col] != '.'){
                    placeWEST(1, row, col, comp);
                    break;
                }
            }
        }while(comp[row][col] == 'x' || comp[row][col] == '.' || free_col < 1);
       
    }
  
    //plasez nava de 1
    for(int i = 0; i < 4; i++){
        do{
            row = getRandoms(0, 9);
            col = getRandoms(0, 9);
            if (comp[row][col] == '@') {
            comp[row - 1][col] = '.';
            comp[row + 1][col] = '.';
            comp[row][col - 1] = '.';
            comp[row][col + 1] = '.';
            comp[row - 1][col - 1] = '.';
            comp[row - 1][col + 1] = '.';
            comp[row + 1][col - 1] = '.';
            comp[row + 1][col + 1] = '.';
            comp[row][col] = 'x';
            break;
            }

        }while(comp[row][col] != '@' || comp[row][col] == '.' || comp[row][col] == 'x');
        
    }
    int k;
    for(int i = 0; i < 10; i++){
        k=0;
        for(int j = 0; j < 20; j++){
            if (j % 2 == 0) comp_aux[i][j] = '|';
            else comp_aux[i][j] = comp[i][k++];  
        }
    }
    //citesc tabelul jucatorului din fisier
    read(jucator, nume); 

}

//functia in care se desfasoara jocul propriu-zis
void game(char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score){
    WINDOW *game_screen = initscr();
    int t = 0; // va tine evidenta cine ataca
    int x = 1, y = 0;
    char c;
    int nrows1;
    int turn = 0;
    srand(time(0)); 
    bkgd(COLOR_PAIR(4));
    keypad(stdscr, TRUE);
    
    char score[20] = "";
    char score1[20] = "";
    char x_pos;
    char y_pos[20] = "";

    int nfds, sel;
    fd_set read_descriptors;
    struct timeval timeout;
    nfds = 1;
    FD_ZERO(&read_descriptors);
    FD_SET(0, &read_descriptors);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    while(1) {
        c = 0;
        clear();
        nrows1 = 0;
        int i,j;
        //afiseaza tabelul calculatorului
        for(i = 0; i < 10; i++){
            for( j = 0; j < 20; j++){
                if(comp_aux[i][j] == 'o'){
                    wattron(game_screen, COLOR_PAIR(1));
                    printw("%c", comp_aux[i][j]);
                    wattron(game_screen, COLOR_PAIR(4));  
                }
                else if (comp_aux[i][j] == '~'){
                    wattron(game_screen, COLOR_PAIR(6));
                    printw("%c",comp_aux[i][j]);
                    wattron(game_screen, COLOR_PAIR(4));
                }
                else if (comp_aux[i][j] == '|')
                    printw("%c", comp_aux[i][j]);
                else printw(" ");
            }
            printw("|");
            wattron(game_screen, COLOR_PAIR(6));
            printw("%d\n", i);
            wattron(game_screen, COLOR_PAIR(4));
        }

        wattron(game_screen, COLOR_PAIR(6));
        printw("|A|B|C|D|E|F|G|H|I|J|\n");
        wattron(game_screen, COLOR_PAIR(2));
        printw("\nPLAYER");
        printw("   Score :");
        sprintf(score, "%d", *jucator_score);
        printw("%s  ", score);
        printw("Position:");
        sprintf(y_pos, "%d", y);
        printw("%s", y_pos);
        if (x == 1) x_pos = 'A';
        else if (x == 3) x_pos = 'B';
        else if (x == 5) x_pos = 'C';
        else if (x == 7) x_pos = 'D';
        else if (x == 9) x_pos = 'E';
        else if (x == 11) x_pos = 'F';
        else if (x == 13) x_pos = 'G';
        else if (x == 15) x_pos = 'H';
        else if (x == 17) x_pos = 'I';
        else if (x == 19) x_pos = 'J';
        printw("%c\n", x_pos);
        wattron(game_screen, COLOR_PAIR(4));
        printw("\n\n");

        //afisare tabelul jucatorului
        nrows1 = 0;
        for (nrows1 = 0; nrows1 < 10; nrows1++){
            for (int j = 0; j < 20; j++ )  {
                if (jucator[nrows1][j] == 'o'){
                    wattron(game_screen, COLOR_PAIR(1));
                    printw("%c", jucator[nrows1][j]);   
                    wattron(game_screen, COLOR_PAIR(4)); 

                }
                else if (jucator[nrows1][j] == 'x'){
                    printw("%c", jucator[nrows1][j]);
                }
            
                else if (jucator[nrows1][j] == '~'){
                    wattron(game_screen, COLOR_PAIR(6));
                    printw("%c", jucator[nrows1][j]);   
                    wattron(game_screen, COLOR_PAIR(4)); 
                }
                else printw("%c", jucator[nrows1][j]);  
            } 
            printw("|");
            wattron(game_screen, COLOR_PAIR(6));
            printw("%d\n", nrows1);
            wattron(game_screen, COLOR_PAIR(4));
        }

        wattron(game_screen, COLOR_PAIR(6));
        printw("|A|B|C|D|E|F|G|H|I|J|\n");
        wattron(game_screen, COLOR_PAIR(2));
        printw("\nCOMPUTER");
        printw("  Score :");
        sprintf(score1, "%d", *comp_score);
        printw("%s\n", score1);
        wattron(game_screen, COLOR_PAIR(4));

        //afisare legenda
        wattron(game_screen, COLOR_PAIR(2));
        mvprintw(15, 60, "        LEGENDA");
        mvprintw(16, 60, "--------------------------");
        mvprintw(17, 60, "|");
        wattron(game_screen, COLOR_PAIR(1));
        mvprintw(17, 61, "  o");
        wattron(game_screen, COLOR_PAIR(2));
        mvprintw(17, 65, "- hitted ship");
        mvprintw(17, 85, "|");
        mvprintw(18, 60, "|");
        wattron(game_screen, COLOR_PAIR(6));
        mvprintw(18, 61, "  ~");
        wattron(game_screen, COLOR_PAIR(2));
        mvprintw(18, 65, "- missed ship, water");
        mvprintw(18, 85, "|");
        mvprintw(19, 60, "|");
        wattron(game_screen, COLOR_PAIR(4));
        mvprintw(19, 61, "  x");
        wattron(game_screen, COLOR_PAIR(2));
        mvprintw(19, 65, "- ship piece");
        mvprintw(19, 85, "|");
        mvprintw(20, 60, "--------------------------");

        //citirea caracterelor de miscare
        sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);

        if (sel > 0) {
            c = getchar();
            t = 0;
        } else {
            t++;
        }
        wattron(game_screen, COLOR_PAIR(2));
        mvprintw(29,15,"--------------------------The PLAYER Attacks!---------------------------");

        wattron(game_screen, COLOR_PAIR(4));
        FD_ZERO(&read_descriptors);
        FD_SET(0, &read_descriptors);

        //secundele in care se va ataca
        timeout.tv_sec = 3; 
        timeout.tv_usec = 0;

        keypad(stdscr, TRUE);

        //navigarea prin joc cu ajutorul tastelor SWAD
        do{
            int row, col;
            if(tolower(c) == 's' && y < 9)  {
                y++;
                wattron(game_screen, COLOR_PAIR(3));
                mvprintw(y, x, "*");
                wattron(game_screen, COLOR_PAIR(4));
            }
            if(tolower(c) == 'w' && y > 0)  {
                y--; 
                wattron(game_screen, COLOR_PAIR(3));
                mvprintw(y, x, "*");
                wattron(game_screen, COLOR_PAIR(4));
            } 
            if(tolower(c) == 'a' && x >= 0) {
                x -= 2;
                wattron(game_screen, COLOR_PAIR(3));
                mvprintw(y, x, "*");
                wattron(game_screen, COLOR_PAIR(4));
            }
            if(tolower(c) == 'd' && x < 19) {
                x += 2;
                wattron(game_screen, COLOR_PAIR(3));
                mvprintw(y, x, "*");
                wattron(game_screen, COLOR_PAIR(4));
            }
            wattron(game_screen, COLOR_PAIR(3));
            mvprintw(y, x, "*");
            wattron(game_screen, COLOR_PAIR(4));

            //daca este selectat ENTER
            if (c == 13) {
                if(comp_aux[y][x] != 'o' && comp_aux[y][x] != '~'){
                    if(comp_aux[y][x] == 'x'){
                        comp_aux[y][x] = 'o';
                        wattron(game_screen, COLOR_PAIR(1));
                        mvprintw(y,x,"o");
                        mvprintw(13,2,"Hit");
                        (*jucator_score)++;
                    }
                    else {     
                        comp_aux[y][x] = '~';
                        wattron(game_screen, COLOR_PAIR(3));
                        mvprintw(y,x,"~");
                        mvprintw(13,7,"Miss");
                        turn = 0; 

                        // daca jucatorul a ratat lovitura
                        //devine randul calculatorului
                        wattron(game_screen, COLOR_PAIR(2));
                        mvprintw(29,15,"--------------------------The COMPUTER Attacks!-------------------------");
                        do{
                            row = getRandoms(0,9);
                            col = getRandoms(0,19);
                            if (jucator[row][col] == 'x'){
                                jucator[row][col] = 'o'; 
                                wattron(game_screen, COLOR_PAIR(1));
                                mvprintw(28,2,"Hit\n"); 
                                wattron(game_screen, COLOR_PAIR(2));
                                (*comp_score)++;
                            }
                            else if (jucator[row][col] != 'x' && jucator[row][col] != '|' && jucator[row][col] != 'o'){
                                    jucator[row][col] = '~';
                                    wattron(game_screen, COLOR_PAIR(3));
                                    mvprintw(28,7,"Miss\n"); 
                                    wattron(game_screen, COLOR_PAIR(2));
                                    break;
                            }
                        }while(turn == 0 && (jucator[row][col] != 'o' || jucator[row][col] != '~' || jucator[row][col] != '|'));
                    }
                }
                wattron(game_screen, COLOR_PAIR(4));
            }
         
        }while (turn == 1);

        //optiunea de a distruge in avans
        if(tolower(c) == 'k') {
            destroy_in_advance(comp_aux, jucator_score, jucator, comp_score);
        }
        mvprintw(31,2,"To move the players' ships use S W A D keys, to select a ship press ENTER, to return to the menu press 'q', to destroy in advance press 'k'!");
        
        // verifica daca avem un castigator
        winner(jucator, comp_aux, comp_score, jucator_score);
        wrefresh(game_screen);

        //optiunea de a reveni la menu
        if(tolower(c) == 'q') {
            clear();
            endwin();
            return;
        }
        
    }
}

//verifica cate nave au fost distruse de computer
//pe tabela jucatorului
int check_player_ships(char **jucator){
    int nave_distruse = 0;
     for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            //nava de 1
            if (jucator[i][j] == 'o' && (jucator[i][j + 2] != 'o' || jucator[i][j + 2] == 'x') //dreapta
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o') //stanga
                && (jucator[i + 1][j] != 'x' && jucator[i + 1][j] != 'o') //jos
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o')) //sus
                nave_distruse++;
   
            if(jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' && jucator[i][j + 4] == 'o' && jucator[i][j + 6] == 'o') 
                nave_distruse++;
            if (jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' && jucator[i + 2][j] == 'o' && jucator[i + 3][j] == 'o') 
                nave_distruse++;
            //nava de 3
            if (jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' && jucator[i][j + 4] == 'o' 
                && (jucator[i][j + 6] != 'x' && jucator[i][j + 6] != 'o' ) 
                && (jucator[i][j + 6] != 'x' && jucator[i][j + 6] != 'o' )  
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o' )) 
                nave_distruse++;
   
    
            if(jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' && jucator[i + 2][j] == 'o' 
                && (jucator[i + 3][j] != 'x' && jucator[i + 3][j] != 'o') 
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o'))
                nave_distruse++;
    
            if (jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' 
                && (jucator[i][j + 4] != 'x' && jucator[i][j + 4] != 'o')
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o'))
                nave_distruse++;
   
            if(jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' 
                && (jucator[i + 2][j] != 'x' && jucator[i + 2][j] != 'o')
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o'))
                nave_distruse++;
        }
    }
    return nave_distruse;
}

//verifica cate nave au fost distruse de jucator
//pe tabela calculatorului
int check_comp_ships(char jucator[12][22]){
    int nave_distruse = 0;
     for (int i = 0; i < 10; i++){
        for (int j = 0; j < 20; j++){
            //verificare nava de 1
            if (jucator[i][j] == 'o' && (jucator[i][j + 2] != 'o' || jucator[i][j + 2] == 'x') //dreapta
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o') //stanga
                && (jucator[i + 1][j] != 'x' && jucator[i + 1][j] != 'o') //jos
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o')) //sus
                nave_distruse++;

            //verificare nava de 4 pe orizontala
            if(jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' && jucator[i][j + 4] == 'o' && jucator[i][j + 6] == 'o') 
                nave_distruse++;
            //verificare nava de 4 pe verticala
            if (jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' && jucator[i + 2][j] == 'o' && jucator[i + 3][j] == 'o') 
                nave_distruse++;

            //verificare nava de 3 pe orizontala
            if (jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' && jucator[i][j + 4] == 'o' 
                && (jucator[i][j + 6] != 'x' && jucator[i][j + 6] != 'o' ) 
                && (jucator[i][j + 6] != 'x' && jucator[i][j + 6] != 'o' )  
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o' )) 
                nave_distruse++;
            //verificare nava de 3 pe verticala
            if(jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' && jucator[i + 2][j] == 'o' 
                && (jucator[i + 3][j] != 'x' && jucator[i + 3][j] != 'o') 
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o'))
                nave_distruse++;   
            
            //verificare nava de 2 pe orizontala
            if (jucator[i][j] == 'o' && jucator[i][j + 2] == 'o' 
                && (jucator[i][j + 4] != 'x' && jucator[i][j + 4] != 'o')
                && (jucator[i][j - 2] != 'x' && jucator[i][j - 2] != 'o'))
                nave_distruse++;
            //verificare nava de 2 pe verticala
            if(jucator[i][j] == 'o' && jucator[i + 1][j] == 'o' 
                && (jucator[i + 2][j] != 'x' && jucator[i + 2][j] != 'o')
                && (jucator[i - 1][j] != 'x' && jucator[i - 1][j] != 'o'))
                nave_distruse++;
        }
    }  
    return nave_distruse;
}

//verifica daca sau acumulat 20 puncte scor
//afiseaza castigatorul si informatiile finale
void winner(char **jucator, char comp_aux[12][22], int *comp_score, int *jucator_score){
    WINDOW *game_win;
    char aux[20] = "";
    char aux1[20] = "";
    char aux2[20] = "";
    char aux3[20] = "";
    int ncols;
    int nave_distruse;
    int nave_distruse2;

    //daca jucatorul este castigator
    if(*jucator_score == 20) {
        game_win = initscr();
        clear();
        noecho();
        cbreak(); 
        curs_set(0);
        refresh();
        start_color();
        ncols = getmaxx(game_win);
        wattron(game_win, COLOR_PAIR(2));
        mvwprintw(game_win, 1, ncols / 2 - 15, "__  ______  __  __   _       ______  _   __");      
        mvwprintw(game_win, 2, ncols / 2 - 15, "\\ \\/ / __ \\/ / / /  | |     / / __ \\/ | / /");
        mvwprintw(game_win, 3, ncols / 2 - 15, " \\  / / / / / / /   | | /| / / / / /  |/ / ");
        mvwprintw(game_win, 4, ncols / 2 - 15, " / / /_/ / /_/ /    | |/ |/ / /_/ / /|  /  ");
        mvwprintw(game_win, 5, ncols / 2 - 15, "/_/\\____/\\____/     |__/|__/\\____/_/ |_/   ");
        
                                          
        mvprintw(8, ncols / 2 - 6, "PLAYER IS THE WINNER!!!");
        mvprintw(9 , ncols / 2 - 6, "PLAYER Score: ");
        sprintf(aux, "%d", *jucator_score);
        mvprintw(9 , ncols / 2 + 8, aux);
        mvprintw(10, ncols / 2 - 6, "COMPUTER Score: ");
        sprintf(aux1, "%d", *comp_score);
        mvprintw(10, ncols / 2 + 10, aux1);
        mvprintw(11, ncols / 2 - 6, "Destroyed ships by PLAYER: ");
        mvprintw(11, ncols / 2 + 22, "10");

        mvprintw(12, ncols / 2 - 6, "Destroyed ships by COMPUTER: ");
        nave_distruse2 = check_player_ships(jucator);
        sprintf(aux3, "%d", nave_distruse2);
        mvprintw(12, ncols / 2 + 24, aux3);
        mvwprintw(game_win, 15, ncols / 2 - 5, "   .-=========-.");      
        mvwprintw(game_win, 16, ncols / 2 - 5, "   \\'-=======-'/");
        mvwprintw(game_win, 17, ncols / 2 - 5, "   _|   .=.   |_");
        mvwprintw(game_win, 18, ncols / 2 - 5, "  ((|  {{1}}  |))");
        mvwprintw(game_win, 19, ncols / 2 - 5, "   \\|   /|\\   |/");
        mvwprintw(game_win, 20, ncols / 2 - 5, "    \\__ '`' __/");      
        mvwprintw(game_win, 21, ncols / 2 - 5, "      _`) (`_");
        mvwprintw(game_win, 22, ncols / 2 - 5, "    _|  .=.  |_");
        mvwprintw(game_win, 23, ncols / 2 - 5, "  _/___________\\_");
        mvwprintw(game_win, 24, ncols / 2 - 5, " /_______________\\");
        endwin();
    }
    //daca computerul este castigator
    else if (*comp_score == 20) 
        {   
            game_win = initscr();
            clear();
            noecho();
            cbreak(); 
            curs_set(0);
            refresh();
            start_color();
            ncols = getmaxx(game_win);
            wattron(game_win, COLOR_PAIR(2));
            
            mvwprintw(game_win, 1, ncols / 2 - 15, "__  ______  __  __   __    ____  ___________");      
            mvwprintw(game_win, 2, ncols / 2 - 15, "\\ \\/ / __ \\/ / / /  / /   / __ \\/ ___/_  __/");
            mvwprintw(game_win, 3, ncols / 2 - 15, " \\  / / / / / / /  / /   / / / /\\__ \\ / / ");
            mvwprintw(game_win, 4, ncols / 2 - 15, " / / /_/ / /_/ /  / /___/ /_/ /___/ // / ");
            mvwprintw(game_win, 5, ncols / 2 - 15, "/_/\\____/\\____/  /_____/\\____//____//_/ ");
            mvprintw(8, ncols / 2 - 4, "COMPUTER IS THE WINNER!!!");
            mvprintw(9, ncols / 2 - 4, "COMPUTER Score: ");
            sprintf(aux1, "%d", *comp_score);
            mvprintw(9, ncols / 2 + 12, aux1);
            mvprintw(10, ncols / 2 - 4, "PLAYER Score: ");
            sprintf(aux, "%d", *jucator_score);
            mvprintw(10, ncols / 2  + 10, aux);
            mvprintw(11, ncols / 2 - 4, "Nave distruse de PLAYER: ");
            nave_distruse = check_comp_ships(comp_aux);
            sprintf(aux2, "%d", nave_distruse);
            mvprintw(11, ncols / 2 + 20, aux2);
            mvprintw(12, ncols / 2 - 4, "Nave distruse de COMPUTER: ");
            mvprintw(12, ncols / 2 + 23, "10"); 
            endwin();
        }
}

//distruge random 10 pozitii de pe ambele tabele
void destroy_in_advance( char comp_aux[12][22], int *jucator_score,char **jucator, int *comp_score){
    int row, col;
    for(int i = 0; i < 10; i++){
        do{
            row = getRandoms(0,9);
            col = getRandoms(0,19);
            if (comp_aux[row][col] == 'x'){
                comp_aux[row][col] = 'o'; 
                (*jucator_score)++;
                break;
            }
            else if (comp_aux[row][col] != 'x' && comp_aux[row][col] != '|' && comp_aux[row][col] != 'o'){
                comp_aux[row][col] = '~';
                break;
            }
        }while(comp_aux[row][col] == 'o' || comp_aux[row][col] == '~' || comp_aux[row][col] == '|');
    }
    for(int i = 0; i < 10; i++){
        do{
            row = getRandoms(0,9);
            col = getRandoms(0,19);
            if (jucator[row][col] == 'x'){
                jucator[row][col] = 'o'; 
                (*comp_score)++;
                break;
            }
            else if (jucator[row][col] != 'x' && jucator[row][col] != '|' && jucator[row][col] != 'o'){
                jucator[row][col] = '~';
                break;
            }
        }while(jucator[row][col] == 'o' || jucator[row][col] == '~' || jucator[row][col] != '|');
    }
}

