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

void c_printLogo(WINDOW*,int);
void c_loginScreen(WINDOW*);
void c_mainMenu(WINDOW*);
void c_patModule(WINDOW*);
void c_introScreen();

//patient windows
void c_basePatientWin(WINDOW*);
void c_newPatientWin(WINDOW*);
void c_viewPatientWin(WINDOW*);
void c_patientLoading(WINDOW*);

void c_baseAppoinWin(WINDOW*);
void c_newAppointWin(WINDOW*);
void c_viewAppointWin(WINDOW*);
void c_appointLoading(WINDOW*);


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
    
    wclear(mainWin);

    //main menu 
    c_mainMenu(mainWin);
   


    //end pdcurses
    endwin();

    return 0;
}

//a function to print the logo instead of copying it in every goddamn time. 0 for main logo, 1 for patient logo, 2 for appint logo
void c_printLogo(WINDOW* menu,int choice) {
    if (choice == 0) {
        mvwprintw(menu, 1, 2, "    __  __    ____   _____           ____     ");
        mvwprintw(menu, 2, 2, "   / / / /   /  _/  / ___/   ____ _ ( __ )    ");
        mvwprintw(menu, 3, 2, "  / /_/ /    / /    \\__ \\   / __ `// __  |    ");
        mvwprintw(menu, 4, 2, " / __  /_  _/ / _  ___/ /_ / /_/ // /_/ /     ");
        mvwprintw(menu, 5, 2, "/_/ /_/(_)/___/(_)/____/(_)\\__, / \\____/      ");
        mvwprintw(menu, 6, 2, "                          /____/              ");
        mvwprintw(menu, 7, 18, "(hiz-gate)");
        mvwprintw(menu, 8, 20, "Group 8");
    }
    else if(choice == 1) {
        mvwprintw(menu, 1, 2, "  _____      _   _            _   ");
        mvwprintw(menu, 2, 2, " |  __ \\    | | (_)          | |  ");
        mvwprintw(menu, 3, 2, " | |__) |_ _| |_ _  ___ _ __ | |_ ");
        mvwprintw(menu, 4, 2, " |  ___/ _` | __| |/ _ \\ '_ \\| __|");
        mvwprintw(menu, 5, 2, " | |  | (_| | |_| |  __/ | | | |_ ");
        mvwprintw(menu, 6, 2, " |_|   \\__,_|\\__|_|\\___|_| |_|\__|");
        mvwprintw(menu, 7, 18, "H.I.S.g8");
        
    }
    else if (choice == 2) {
        mvwprintw(menu, 1, 2, "    _                  _     _                 _      ");
        mvwprintw(menu, 2, 2, "   /_\\  _ __ _ __  ___(_)_ _| |_ _ __  ___ _ _| |_ ___");
        mvwprintw(menu, 3, 2, "  / _ \\| '_ \\ '_ \\/ _ \\ | ' \\  _| '  \\/ -_) ' \\  _(_-<");
        mvwprintw(menu, 4, 2, " /_/ \\_\\ .__/ .__/\\___/_|_||_\\__|_|_|_\\___|_||_\\__/__/");
        mvwprintw(menu, 5, 2, "       |_|  |_|                                       ");
        mvwprintw(menu, 6, 18, "H.I.S.g8");

    }
    
};
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
//a function to draw the login screen
void c_loginScreen(WINDOW* win) {
    clear();
    char usr[MAX_SIZE], pass[MAX_SIZE];

    box(win, 0, 0);
    c_printLogo(win,0);
    mvwprintw(win, 28, 2, "// Login-Screen , utilizing a usrnme and pswrd (accepts anything atm cause no time)");
    //login box
    mvwprintw(win, 13, 50, "Login:");
    wgetstr(win, usr);
    mvwprintw(win, 13, 57, usr);
    wrefresh(win);
    mvwprintw(win, 14, 47, "Password:");
    wgetstr(win, pass);
    //meme.push_back('\0');
    mvwprintw(win, 14, 57, pass);
    mvwprintw(win, 16, 50, "Press any key to login");
    wrefresh(win);
}
//a function to draw the main menu and selection process
//TODO: bind to other windows/modules of the program
void c_mainMenu(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 0);
    mvwprintw(win, 9, 3, "Logged in as: Mary Jane | Reception Desk");
    mvwprintw(win, 9, 75, "Main Menu");

    int choice, highlight = 0;
    std::string m_options[4] = { "Patient Management","Appointment Management"," ","Sign Out/Exit" };
    mvwprintw(win, 28, 2, "// Main Menu Concept, showing the 2 modules plus signout/exit and maybe a settings page");
    while (1) {
        for (int i = 0; i < 4; i++) {
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
            if (highlight == 4) {
                highlight = 3;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                c_basePatientWin(win);
                break;
            case 1:
                c_baseAppoinWin(win);
                break;
            case 3:
                break;
            case 4:
                break;
                    
            }
            
            break;
        }
    }

    wrefresh(win);
}

void c_basePatientWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 1);

    int choice, highlight = 0;
    std::string m_options[3] = { "View a patient info","Add a new patient","Main Menu"};
    mvwprintw(win, 28, 2, "// base patient module UI, showing the 2 options:view or add a new patient info");
    while (1) {
        for (int i = 0; i < 3; i++) {
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
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 3) {
                highlight = 2;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                
                break;
            case 1:
                break;
            case 2:
                c_mainMenu(win);
                break;

            }
            //clear();
           break;
        }
        
    }
    wrefresh(win);
    
}



void c_baseAppoinWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 2);

    int choice, highlight = 0;
    std::string m_options[3] = { "View appointments","Add a new appointment","Main Menu" };
    mvwprintw(win, 28, 2, "// base appointment module UI, showing the 2 options:view or add a new appointment");
    while (1) {
        for (int i = 0; i < 3; i++) {
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
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 3) {
                highlight = 2;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:

                break;
            case 1:
                break;
            case 2:
                c_mainMenu(win);
                break;

            }
            //clear();
            break;
        }

    }
    wrefresh(win);

}

