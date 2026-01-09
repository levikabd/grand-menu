#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <locale>
#include <iostream>

#include <string>

int runProgFirst()
{
    std::wcout << L"Run the first program!\n";
    wchar_t wc;
    std::wcin >> wc;
    return 0;
};

int runProgSecond()
{
    std::wcout << L"Run the second program!\n";
    wchar_t wc;
    std::wcin >> wc;
    return 0;
};

int runProgThird()
{
    std::wcout << L"Run the third program!\n";
    wchar_t wc;
    std::wcin >> wc;
    return 0;
};

int initWindowPre(MENU *my_menu, WINDOW *stdscr)
{
    setlocale(LC_ALL, "");
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    set_menu_win(my_menu, stdscr);
    set_menu_mark(my_menu, "> ");
    set_menu_opts(my_menu, O_SHOWDESC);

    set_menu_fore(my_menu, COLOR_PAIR(2));
    set_menu_back(my_menu, COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    box(stdscr, ACS_VLINE, ACS_HLINE);
    mvwaddch(stdscr, 0, 0, ACS_ULCORNER);
    mvwaddch(stdscr, 0, COLS-1, ACS_URCORNER);
    mvwaddch(stdscr, LINES-1, 0, ACS_LLCORNER);
    mvwaddch(stdscr, LINES-1, COLS-1, ACS_LRCORNER);
    attroff(COLOR_PAIR(3));
    
    post_menu(my_menu);
    refresh();

    return 0;
};

int closeWindow(MENU *my_menu, ITEM **my_items)
{
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(int i = 0; i < 4; i++) {
        free_item(my_items[i]);
    };
    free(my_items);
    endwin();
    return 0;
};

int main() {
    MENU *my_menu;
    ITEM **my_items;
    WINDOW *stdscr;

    stdscr = initscr();
    
    const char *choices[] = {
        "Run the first  program",
        "Run the second program",
        "Run the third  program",
        "Exit",
        (char *)NULL
    };
    
    my_items = (ITEM **)calloc(4, sizeof(ITEM *));
    for(int i = 0; i < 4; i++) {
        my_items[i] = new_item(choices[i], "");
    };

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);  // Красный
    init_pair(2, COLOR_BLUE, COLOR_BLACK); // Синий
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Голубой

    my_menu = new_menu(my_items);

    initWindowPre(my_menu, stdscr);
    
    int choice=0;
    do {
        choice = getch();

        if (choice==KEY_DOWN)
        {
            menu_driver(my_menu, REQ_DOWN_ITEM);
        }else if (choice==KEY_UP){
            menu_driver(my_menu, REQ_UP_ITEM);
        }else if (choice==10){  // Enter
            move(LINES-2, 0);
            clrtoeol();
            attron(COLOR_PAIR(2));
            mvprintw(LINES-2, 0, "Selected: %s", item_name(current_item(my_menu)));
            attroff(COLOR_PAIR(2));

            std::string itName = item_name(current_item(my_menu));

            if (itName=="Exit") 
            {
                choice = 'q';
            }else if (itName=="Run the first  program") 
            {
                runProgFirst();
                            
                choice=0;
            }else if (itName=="Run the second program") 
            {
                runProgSecond();
                
                choice=0;
            }else if (itName=="Run the third  program") 
            {
                runProgThird();
                                
                choice=0;
            };

        }else if (choice=='q'){ 
            break;
        };


        refresh();        
        wrefresh(stdscr);
    } while(choice != 'q');
    
    closeWindow(my_menu, my_items);
    
    return 0;
};
