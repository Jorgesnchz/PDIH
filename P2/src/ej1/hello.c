#include <ncurses.h>

int main() {
    initscr();
    printw("Holita");
    refresh();
    getch();
    endwin();
    return 0;
}
