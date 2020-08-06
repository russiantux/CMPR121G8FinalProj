//FINAL PROJ | GROUP 8
#include <iostream>
#include "common_vars.h"
#include "UI.h"


//These functions are where most of the UI panels are, to avoid cluttering up int main()
int main()
{
    initscr();
   // noecho();
    clear();
    UI window;
    WINDOW* mainWin = newwin(30, 120, 0, 0);
    window.c_introScreen();
    getch();
    clear();
    //generate the main window
    refresh();
    window.c_loginScreen(mainWin);
    wclear(mainWin);
    //main menu 
    window.c_mainMenu(mainWin);
    //end pdcurses
    endwin();
    return 0;
}

