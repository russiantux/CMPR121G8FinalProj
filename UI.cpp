#include "UI.h"

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

char name[50],age[12], gender[10], dob[50], mStatus[50], address[100], pConMet[50], homeNum[50], workNum[50], email[50], iName[50], ipNum[50], iNum[50], iBill[100], pcp[50], refP[50], pcpNum[50], refPnum[50], ecName[50], ecNum[50], ecRel[50];


//a function to print the logo instead of copying it in every goddamn time. 0 for main logo, 1 for patient logo, 2 for appint logo
void UI::c_printLogo(WINDOW* menu, int choice) {
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
    else if (choice == 1) {
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
void UI::c_introScreen() {
    move(13, 5);
    attron(A_STANDOUT);
    printw("The following screens shown here are non-working concepts, subject to change thoughout all-nighter development");
    move(14, 15);
    printw("Press any key to proceed.");
    attroff(A_STANDOUT);
    refresh();
}
//a function to draw the login screen
void UI::c_loginScreen(WINDOW* win) {
    clear();
    char usr[50], pass[50];

    box(win, 0, 0);
    c_printLogo(win, 0);
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
void UI::c_mainMenu(WINDOW* win) {
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
//base patient module win
void UI::c_basePatientWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 1);

    int choice, highlight = 0;
    std::string m_options[3] = { "View a patient info","Add a new patient","Main Menu" };
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
                c_viewmPatientWin(win);
                break;
            case 1:
                c_newPatientWin(win);
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


//sub viewing of patient module win
void UI::c_viewmPatientWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 1);

    int choice, highlight = 0;
    std::string m_options[3] = { "concept","View a patient","Back" };
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
                c_viewPatientConceptWin(win);
                break;
            case 1:
                c_viewPatientWin(win);
                break;
            case 2:
                c_basePatientWin(win);
                break;

            }
            //clear();
            break;
        }

    }
    wrefresh(win);
}

void UI::c_viewPatientConceptWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);

    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Patient file for John Doe:");
    wattroff(win, A_REVERSE);
    //row 1
    wattron(win, A_REVERSE);
    mvwprintw(win, 3, 4, "General Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 4, 2, "Name(Last,First): John Doe");
    mvwprintw(win, 4, 30, "Age: 30");
    mvwprintw(win, 4, 39, "DoB: 02/29/1980");
    mvwprintw(win, 4, 57, "Gender: MALE");
    mvwprintw(win, 4, 72, "Marital Status: MARRIED");
    //row2
    mvwprintw(win, 5, 2, "Address: 123 Test St., Test CA, 123456");
    mvwprintw(win, 5, 42, "Perfered Contact Method: WORK PHONE");
    //row3
    wattron(win, A_REVERSE);
    mvwprintw(win, 7, 4, "Patient Contact Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 8, 2, "Phone number (home): (123) 456-7890");
    mvwprintw(win, 8, 40, "Phone number (work): (098) 765-4321");
    mvwprintw(win, 8, 78, "Email: jdoe1980@email.com");
    //row4
    wattron(win, A_REVERSE);
    mvwprintw(win, 10, 4, "Insurence/PCP");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 11, 2, "Insurence Co. : Health Insurence Corp.");
    mvwprintw(win, 11, 42, "Insurence Phone: (123) 123-4567");
    mvwprintw(win, 11, 76, "Insurence #: 123-45-67889");
    mvwprintw(win, 12, 2, "Insurence Billing Address: 123456 Health Corp Way, Health CA, 198765");

    mvwprintw(win, 13, 2, "Refering Physician: Dr.Doc McDoctor Md.");
    mvwprintw(win, 13, 44, "Primary Care Physician: Dr.Doc McDoc II Md.");
    mvwprintw(win, 14, 2, "R.P. #: (123) 321-3241");
    mvwprintw(win, 14, 27, "P.C.P. #: (123) 829-9332");

    wattron(win, A_REVERSE);
    mvwprintw(win, 16, 4, "EMERGANCY CONTACT");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 17, 2, "E.C. Name: Stacy Doe");
    mvwprintw(win, 17, 24, "E.C. #: (123) 123-1232");
    mvwprintw(win, 17, 49, "E.C. Relationship: SPOUSE");

    wattron(win, A_REVERSE);
    mvwprintw(win, 20, 2, "Upcoming Appointments");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 21, 2, "- CHECK-UP/FOLLOW UP | AUG 18 2020 @ 12:00pm");

    int choice, highlight = 0;
    std::string m_options[2] = { "View Notes","Back" };
    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                c_viewPatientConceptNotesWin(win);
                break;
            case 1:
                c_viewmPatientWin(win);

                break;
            }
            //clear();
            break;
        }

    }

    wrefresh(win);



}

void UI::c_viewPatientConceptNotesWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);

    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Patient Notes for John Doe:");
    wattroff(win, A_REVERSE);

    mvwprintw(win, 3, 2, "07/28/2020 - PATIENT HAD CHECK-UP,COMPLAINED ABOUT HEADACHES, PERSCRIBED [medication], MADE FOLLOW UP APPT.");
    mvwprintw(win, 5, 2, "03/13/2020 - PATIENT HAD CHECK-UP, VITALS AND HEALTH ARE NORMAL. NEW APPT MADE FOR 07/28/2020");
    mvwprintw(win, 7, 2, "12/10/2019 - PATIENT HAD CHECH-UP, VITALS AND HEALTH ARE NORMAL. NEW APPT MADE FOR 03/13/2020");

    int choice, highlight = 0;
    std::string m_options[2] = { "View Patient File","Back" };
    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                c_viewPatientConceptWin(win);
                break;
            case 1:
                c_viewmPatientWin(win);
                break;
            }
            //clear();
            break;
        }

    }
    wrefresh(win);
}

void UI::c_newPatientWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);

    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "New Patient");
    wattroff(win, A_REVERSE);
    //row 1
    wattron(win, A_REVERSE);
    mvwprintw(win, 3, 4, "General Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 4, 2, "Name(Last,First):");
    wgetstr(win, name);
    mvwprintw(win, 4, 30, "Age:");
    wgetstr(win, age);
    mvwprintw(win, 4, 39, "DoB:");
    wgetstr(win, dob);
    mvwprintw(win, 4, 57, "Gender:");
    wgetstr(win, gender);
    mvwprintw(win, 4, 72, "Marital Status:");
    wgetstr(win, mStatus);
    //row2
    mvwprintw(win, 5, 2, "Address:");
    wgetstr(win, address);
    mvwprintw(win, 5, 42, "Perfered Contact Method:");
    wgetstr(win, pConMet);
    //row3
    wattron(win, A_REVERSE);
    mvwprintw(win, 7, 4, "Patient Contact Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 8, 2, "Phone number (home):");
    wgetstr(win, homeNum);
    mvwprintw(win, 8, 40, "Phone number (work):");
    wgetstr(win, workNum);
    mvwprintw(win, 8, 78, "Email:");
    wgetstr(win, email);
    //row4
    wattron(win, A_REVERSE);
    mvwprintw(win, 10, 4, "Insurence/PCP");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 11, 2, "Insurence Co. :");
    wgetstr(win, iName);
    mvwprintw(win, 11, 42, "Insurence Phone:");
    wgetstr(win, ipNum);
    mvwprintw(win, 11, 76, "Insurence #:");
    wgetstr(win, iNum);
    mvwprintw(win, 12, 2, "Insurence Billing Address:");
    wgetstr(win, iBill);

    mvwprintw(win, 13, 2, "Refering Physician:");
    wgetstr(win, refP);
    mvwprintw(win, 13, 44, "Primary Care Physician:");
    wgetstr(win, pcp);
    mvwprintw(win, 14, 2, "R.P. #");
    wgetstr(win, refPnum);
    mvwprintw(win, 14, 27, "P.C.P. #:");
    wgetstr(win, pcpNum);

    wattron(win, A_REVERSE);
    mvwprintw(win, 16, 4, "EMERGANCY CONTACT");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 17, 2, "E.C. Name:");
    wgetstr(win, ecName);
    mvwprintw(win, 17, 24, "E.C. #:");
    wgetstr(win, ecNum);
    mvwprintw(win, 17, 49, "E.C. Relationship:");
    wgetstr(win, ecRel);

    

    int choice, highlight = 0;
    std::string m_options[2] = { "Yes","No"};
    while (1) {
        mvwprintw(win, 19, 80, "Is everything correct?");
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
                c_viewmPatientWin(win);
                break;
            case 1:
                c_newPatientWin(win);
                break;
            }
            //clear();
            break;
        }

    }

    wrefresh(win);



}

void UI::c_viewPatientWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);

    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Patient file for ");
    mvwprintw(win, 1, 19, name);
    wattroff(win, A_REVERSE);
    //row 1
    wattron(win, A_REVERSE);
    mvwprintw(win, 3, 4, "General Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 4, 2, "Name(Last,First):");
    mvwprintw(win, 4, 20, name);
    mvwprintw(win, 4, 30, "Age:");
    mvwprintw(win, 4, 35, age);
    mvwprintw(win, 4, 39, "DoB:");
    mvwprintw(win, 4, 44, dob);
    mvwprintw(win, 4, 57, "Gender:");
    mvwprintw(win, 4, 66, gender);
    mvwprintw(win, 4, 72, "Marital Status:");
    mvwprintw(win, 4, 89, mStatus);
    //row2
    mvwprintw(win, 5, 2, "Address:");
    mvwprintw(win, 5, 12, address);
    mvwprintw(win, 5, 42, "Perfered Contact Method:");
    mvwprintw(win, 5, 68, pConMet);
    //row3
    wattron(win, A_REVERSE);
    mvwprintw(win, 7, 4, "Patient Contact Info");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 8, 2, "Phone number (home):");
    mvwprintw(win, 8, 24, homeNum);
    mvwprintw(win, 8, 40, "Phone number (work):");
    mvwprintw(win, 8, 62, workNum);
    mvwprintw(win, 8, 78, "Email:");
    mvwprintw(win, 8, 86, email);
    //row4
    wattron(win, A_REVERSE);
    mvwprintw(win, 10, 4, "Insurence/PCP");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 11, 2, "Insurence Co. :");
    mvwprintw(win, 11, 19, iName);
    mvwprintw(win, 11, 42, "Insurence Phone:");
    mvwprintw(win, 11, 60, ipNum);
    mvwprintw(win, 11, 76, "Insurence #:");
    mvwprintw(win, 11, 90, iNum);
    mvwprintw(win, 12, 2, "Insurence Billing Address:");
    mvwprintw(win, 12, 30, iBill);

    mvwprintw(win, 13, 2, "Refering Physician:");
    mvwprintw(win, 13, 23, refP);
    mvwprintw(win, 13, 44, "Primary Care Physician:");
    mvwprintw(win, 13, 69, pcp);
    mvwprintw(win, 14, 2, "R.P. #:");
    mvwprintw(win, 14, 11, refPnum);
    mvwprintw(win, 14, 27, "P.C.P. #:");
    mvwprintw(win, 14, 38, pcpNum);

    wattron(win, A_REVERSE);
    mvwprintw(win, 16, 4, "EMERGANCY CONTACT");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 17, 2, "E.C. Name:");
    mvwprintw(win, 17, 14, ecName);
    mvwprintw(win, 17, 24, "E.C. #:");
    mvwprintw(win, 17, 33, ecNum);
    mvwprintw(win, 17, 49, "E.C. Relationship:");
    mvwprintw(win, 17, 69, ecRel);

    wattron(win, A_REVERSE);
    mvwprintw(win, 20, 2, "Upcoming Appointments");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 21, 2, "- not working, fix me pls | AUG 18 2020 @ 12:00pm");

    int choice, highlight = 0;
    std::string m_options[1] = { "Back" };
    while (1) {
        for (int i = 0; i < 1; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
            
                c_viewmPatientWin(win);

                break;
            }
            //clear();
            break;
        }

    }

    wrefresh(win);



}

void UI::c_baseAppoinWin(WINDOW* win) {
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
                c_viewmAppointWin(win);
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

void UI::c_viewmAppointWin(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);
    c_printLogo(win, 2);

    int choice, highlight = 0;
    std::string m_options[3] = { "concept","View Appointments","Back" };
    mvwprintw(win, 28, 2, "// base viewing appointment module UI");
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
                c_viewAppointConceptwk123Win(win);
                break;
            case 1:
                c_viewAppointConceptwk123Win(win);
                break;
            case 2:
                c_baseAppoinWin(win);
                break;

            }
            //clear();
            break;
        }

    }
    wrefresh(win);
}

void UI::c_viewAppointConceptwk123Win(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);


    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Appointments for August");
    wattroff(win, A_REVERSE);

    wattron(win, A_REVERSE);
    mvwprintw(win, 2, 4, "Week 1");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 3, 2, "Monday:");
    mvwprintw(win, 4, 3, "12:00pm - [name]");
    mvwprintw(win, 5, 3, "12:30pm - [name]");
    mvwprintw(win, 6, 3, "2:45pm - [name]");
    mvwprintw(win, 7, 3, "4:00pm - [name]");
    mvwprintw(win, 8, 3, "4:30pm - [name]");

    mvwprintw(win, 3, 21, "Tuesday:");
    mvwprintw(win, 4, 22, "12:00pm - [name]");

    mvwprintw(win, 8, 22, "4:30pm - [name]");

    mvwprintw(win, 3, 52, "Thursday:");
    mvwprintw(win, 4, 51, "12:00pm - [name]");
    mvwprintw(win, 5, 51, "12:30pm - [name]");
    mvwprintw(win, 6, 51, "2:45pm - [name]");
    mvwprintw(win, 7, 51, "4:00pm - [name]");


    mvwprintw(win, 3, 71, "Friday:");
    
    mvwprintw(win, 6, 70, "2:45pm - [name]");
    mvwprintw(win, 7, 70, "4:00pm - [name]");
    mvwprintw(win, 8, 70, "4:30pm - [name]");


    wattron(win, A_REVERSE);
    mvwprintw(win, 10, 4, "Week 2");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 11, 2, "Monday:");
    mvwprintw(win, 12, 3, "12:00pm - [name]");
    mvwprintw(win, 13, 3, "12:30pm - [name]");
    mvwprintw(win, 14, 3, "2:45pm - [name]");
    mvwprintw(win, 15, 3, "4:00pm - [name]");
    mvwprintw(win, 16, 3, "4:30pm - [name]");

    mvwprintw(win, 11, 21, "Tuesday:");
    mvwprintw(win, 12, 22, "12:00pm - [name]");
    mvwprintw(win, 13, 22, "12:30pm - [name]");


    mvwprintw(win, 11, 52, "Thursday:");
  
    mvwprintw(win, 12, 51, "4:30pm - [name]");


    mvwprintw(win, 11, 71, "Friday:");
    mvwprintw(win, 12, 70, "12:00pm - [name]");
    mvwprintw(win, 13, 70, "12:30pm - [name]");
    mvwprintw(win, 14, 70, "2:45pm - [name]");

    wattron(win, A_REVERSE);
    mvwprintw(win, 18, 4, "Week 3");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 19, 2, "Monday:");
   
    mvwprintw(win, 20, 3, "12:30pm - [name]");
    mvwprintw(win, 21, 3, "2:45pm - [name]");
    mvwprintw(win, 22, 3, "4:00pm - [name]");
    mvwprintw(win, 23, 3, "4:30pm - [name]");

    mvwprintw(win, 19, 21, "Tuesday:");
    mvwprintw(win, 20, 22, "12:00pm - [name]");
    mvwprintw(win, 21, 22, "12:30pm - [name]");
    mvwprintw(win, 22, 22, "2:45pm - [name]");
    mvwprintw(win, 23, 22, "4:00pm - [name]");
    mvwprintw(win, 24, 22, "4:30pm - [name]");


    mvwprintw(win, 19, 52, "Thursday:");
    mvwprintw(win, 20, 51, "12:00pm - [name]");
 
    mvwprintw(win, 21, 51, "4:30pm - [name]");


    mvwprintw(win, 19, 71, "Friday:");
    mvwprintw(win, 20, 70, "12:00pm - [name]");
    mvwprintw(win, 21, 70, "12:30pm - [name]");
    mvwprintw(win, 22, 70, "2:45pm - [name]");
    mvwprintw(win, 23, 70, "4:00pm - [name]");
    mvwprintw(win, 24, 70, "4:30pm - [name]");

    int choice, highlight = 0;
    std::string m_options[2] = { "View Week 4","Back" };
    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                c_viewAppointConceptwk4Win(win);
                break;
            case 1:
                c_viewmAppointWin(win);

                break;
            }
            //clear();
            break;
        }

    }

    wrefresh(win);
}

void UI::c_viewAppointConceptwk4Win(WINDOW* win) {
    wclear(win);
    wrefresh(win);
    keypad(win, true);
    box(win, 0, 0);


    wattron(win, A_REVERSE);
    mvwprintw(win, 1, 1, "Appointments for August");
    wattroff(win, A_REVERSE);

    wattron(win, A_REVERSE);
    mvwprintw(win, 2, 4, "Week 4");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 3, 2, "Monday:");
    mvwprintw(win, 4, 3, "12:00pm - [name]");
    mvwprintw(win, 5, 3, "12:30pm - [name]");
    mvwprintw(win, 6, 3, "2:45pm - [name]");
    mvwprintw(win, 7, 3, "4:00pm - [name]");
    mvwprintw(win, 8, 3, "4:30pm - [name]");

    mvwprintw(win, 3, 21, "Tuesday:");
    mvwprintw(win, 4, 22, "12:00pm - [name]");
    mvwprintw(win, 5, 22, "12:30pm - [name]");
    mvwprintw(win, 6, 22, "2:45pm - [name]");
    mvwprintw(win, 7, 22, "4:00pm - [name]");
    mvwprintw(win, 8, 22, "4:30pm - [name]");

    mvwprintw(win, 3, 52, "Thursday:");
    mvwprintw(win, 4, 51, "12:00pm - [name]");
    mvwprintw(win, 5, 51, "12:30pm - [name]");
    mvwprintw(win, 6, 51, "2:45pm - [name]");
    mvwprintw(win, 7, 51, "4:00pm - [name]");
    mvwprintw(win, 8, 51, "4:30pm - [name]");

    mvwprintw(win, 3, 71, "Friday:");
    mvwprintw(win, 4, 70, "12:00pm - [name]");
    mvwprintw(win, 5, 70, "12:30pm - [name]");
    mvwprintw(win, 6, 70, "2:45pm - [name]");
    mvwprintw(win, 7, 70, "4:00pm - [name]");
    mvwprintw(win, 8, 70, "4:30pm - [name]");


    int choice, highlight = 0;
    std::string m_options[2] = { "View Week 3/4","Back" };
    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 20, 100, m_options[i].c_str());
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
            if (highlight == 2) {
                highlight = 1;
            };
            break;
        default:
            break;
        };

        if (choice == 10) {
            switch (highlight) {
            case 0:
                c_viewAppointConceptwk123Win(win);
                break;
            case 1:
                c_viewmAppointWin(win);

                break;
            }
            //clear();
            break;
        }

    }

    wrefresh(win);
}

//damn if i had another month i could have made this work alot better with the other modules. too bad!
