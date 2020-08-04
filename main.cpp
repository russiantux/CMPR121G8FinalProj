/*
The UI is using a library called PDCurses(Public Domain Curses), and allows for (relativly)easy modification of text and it's layout in a console window.
Basic rundown of PDCurses commands:
    BASICS/INIT/DESTRUCTION
    - PDCurses works mainly by modifying the console/program's memory, then being refreshed by the code to update the screen. It is very important to refresh() the memory, otherwise any
      changes you make to the memory will not show up automaticlly.
    - To initilize PDCurses and load it into memory, we always start it with initsrc() at the beginning of the UI code
    - To destroy PDCurses and remove it from memory, at the end we always end it with endsrc();

    MOVE CURSOR
    -PDCurses allows for the console cursor to be moved around with easy, allowing for easy layout of text and objects instead of using setw() everywhere
    -To move the cursor and add text to that moved cursor, we first call move(y,x), the y being which line to print to and the x being where which coloum to write too. (idk why it uses (y,x) instead of (x,y), thats how it's made i guess)
    -After moving the cursor, we would add printw("[insert whatever string here]"), rinse and repeat for each line/piece of text you want to add

    WINDOWS
    - PDCurses has a functionaliy called 'windows' that allow just that distinct window selected to be modified within.(ie. add borders surrounding the 'window' or pin inputs/text to a window)
    - Skys the limit really, when it comes to windows and how to utilize them, people even made games using this library.

    GETTING INPUT
    - Using the call getch(), the program will wait for any time of input from the keyboard, including support for getting which arrow key you pressed.
    - With getch(), you can assign it to a int varible and go ham with that (ie. int c = getch();)
    - For getting input from a specific window, you can use wgetch([pointer to window obj]). You can also assign it to a varible as well.
*/
//#pragma comment(lib,"pdcurses/wincon/pdcurses.lib")

#include <iostream>
#include "common_vars.h"
//the pdcurses header
#include "pdcurses/curses.h"

//These functions are where most of the UI panels are, to avoid cluttering up int main()

void c_printLogo(WINDOW*);
void c_loginScreen(WINDOW*);
void c_mainMenu(WINDOW*);
void c_patModule(WINDOW*);
void c_introScreen();

char* passHash(char*);

int main()
{
    initscr();
    noecho();
    clear();
    c_introScreen();
    getch();
    clear();

    //generate the main window
    WINDOW* mainWin = newwin(30, 120, 0, 0);

    refresh();
    c_loginScreen(mainWin);
    getch();
    wclear(mainWin);

    //main menu 
    c_mainMenu(mainWin);
    getch();


    //end pdcurses
    endwin();

    return 0;
}

//func to show intro msgs,warnings etc.
void c_introScreen() {
    move(13, 5);
    attron(A_STANDOUT);
    printw("The following screens shown here are non-working concepts, subject to change thoughout all-nighter development");
    move(14, 15);
    printw("Press any key to proceed.");
    attroff(A_STANDOUT);
    refresh();
}

//a function to print the logo instead of copying it in every goddamn time
void c_printLogo(WINDOW* menu) {
    mvwprintw(menu, 1, 2, "    __  __    ____   _____           ____     ");
    mvwprintw(menu, 2, 2, "   / / / /   /  _/  / ___/   ____ _ ( __ )    ");
    mvwprintw(menu, 3, 2, "  / /_/ /    / /    \\__ \\   / __ `// __  |    ");
    mvwprintw(menu, 4, 2, " / __  /_  _/ / _  ___/ /_ / /_/ // /_/ /     ");
    mvwprintw(menu, 5, 2, "/_/ /_/(_)/___/(_)/____/(_)\\__, / \\____/      ");
    mvwprintw(menu, 6, 2, "                          /____/              ");
    mvwprintw(menu, 7, 18, "(hiz-gate)");
    mvwprintw(menu, 8, 20, "Group 8");
};

//a function to draw the login screen
void c_loginScreen(WINDOW* win) {
    char usr[MAX_SIZE], pass[MAX_SIZE];
    //char* meme;
   // meme[1] = '1';
    //sizeof(meme);
    box(win, 0, 0);
    c_printLogo(win);
    //login box
    mvwprintw(win, 13, 50, "Login:");
    wgetstr(win, usr);
    mvwprintw(win, 13, 57, usr);
    wrefresh(win);
    mvwprintw(win, 14, 47, "Password:");
    wgetstr(win, pass);
    //meme.push_back('\0');
    mvwprintw(win, 14, 57, pass);
    wrefresh(win);
    mvwprintw(win, 28, 2, "// Login-Screen Concept, utilizing a usrnme and pswrd, subject to change ofc");
    getch();

    wrefresh(win);
}

//a function to draw the main menu and selection process
//TODO: bind to other windows/modules of the program
void c_mainMenu(WINDOW* win) {
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win);
    mvwprintw(win, 9, 3, "Logged in as: Mary Jane | Reception Desk");
    mvwprintw(win, 9, 75, "Main Menu");

    int choice, highlight = 0;
    std::string m_options[5] = { "Patient Management","Appointment Management"," ","Settings","Sign Out/Exit" };
    mvwprintw(win, 28, 2, "// Main Menu Concept, showing the 2 modules plus signout/exit and maybe a settings page");
    while (1) {
        for (int i = 0; i < 5; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 11, 75, m_options[i].c_str());
            wattroff(win, A_REVERSE);

        }
        choice = wgetch(win);

        switch (choice) {
        case KEY_UP:
            highlight--;
            if (highlight == -1) {
                highlight = 0;
            };
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 2) {
                highlight = 3;
            };
            if (highlight == 5) {
                highlight = 4;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            clear();
            break;
        }
    }

    wrefresh(win);
}

/* buggy code, will fix later
char* passHash(char* pass) {
    int l,i=0;
    char hash[50];

    while (pass[i] != '\0') {
        hash[i] = '*';
        i++;
    }
    return hash;
}
*/
