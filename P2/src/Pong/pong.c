#include <ncurses.h>
#include <unistd.h>

#define DELAY 70000
#define WIDTH 80
#define HEIGHT 24
#define PADDLE_HEIGHT 4

void draw_paddle(int y, int x) {
    for (int i = 0; i < PADDLE_HEIGHT; ++i) {
        mvprintw(y + i, x, "|");
    }
}

int main() {
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int ball_dir_x = 1, ball_dir_y = 1;

    int left_paddle_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
    int right_paddle_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;

    int left_score = 0, right_score = 0;
    int ch;

    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (1) {
        clear();

        // Dibujar palas
        draw_paddle(left_paddle_y, 2);
        draw_paddle(right_paddle_y, WIDTH - 3);

        // Dibujar pelota
        mvprintw(ball_y, ball_x, "o");

        // Dibujar marcador
        mvprintw(0, WIDTH / 2 - 10, "P1: %d   P2: %d", left_score, right_score);

        refresh();
        usleep(DELAY);

        // Mover pelota
        ball_x += ball_dir_x;
        ball_y += ball_dir_y;

        // Rebotar en bordes superior/inferior
        if (ball_y <= 1 || ball_y >= HEIGHT - 1)
            ball_dir_y *= -1;

        // Rebotar con palas
        if (ball_x == 3 && ball_y >= left_paddle_y && ball_y < left_paddle_y + PADDLE_HEIGHT)
            ball_dir_x *= -1;

        if (ball_x == WIDTH - 4 && ball_y >= right_paddle_y && ball_y < right_paddle_y + PADDLE_HEIGHT)
            ball_dir_x *= -1;

        // Punto para el jugador derecho
        if (ball_x <= 0) {
            right_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dir_x = 1;
            ball_dir_y = (ball_dir_y == 0) ? 1 : ball_dir_y;
        }

        // Punto para el jugador izquierdo
        if (ball_x >= WIDTH - 1) {
            left_score++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_dir_x = -1;
            ball_dir_y = (ball_dir_y == 0) ? -1 : ball_dir_y;
        }

        // Controles de palas
        ch = getch();
        if (ch == 'q') break;

        if (ch == 'w' && left_paddle_y > 1)
            left_paddle_y--;if (ch == 's' && left_paddle_y + PADDLE_HEIGHT < HEIGHT - 1)
            left_paddle_y++;
        if (ch == KEY_UP && right_paddle_y > 1)
            right_paddle_y--;
        if (ch == KEY_DOWN && right_paddle_y + PADDLE_HEIGHT < HEIGHT - 1)
            right_paddle_y++;
    }

    endwin();
    return 0;
}
