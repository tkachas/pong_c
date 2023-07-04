/*Copyright Eyesphou, Kashmirg, Trustben*/
#include <ncurses.h>
#include <stdio.h>

char border_x;
char border_y = '|';
char paddle_1 = '|';
char paddle_2 = '|';
char ball = 'o';
int left_platform = 13, right_platform = 13;
char lift;
int y = 13, x = 40;
int x_speed = -1, y_speed = 1;
int win = 0;
int score_1 = 0, score_2 = 20;

int borders(int left_platform, int right_platform);
int coord_of_ball(int left_platform, int right_platform);

void increase_score() {
  if (win == 1) {
    score_2++;
  } else if (win == -1) {
    score_1++;
  }
  win = 0;
}

void render_page() {
  clear();
  printw("|Manual\n");
  printw("|1. Press A and Z to control the left platform (up - down). \n");
  printw("|2. Press K and M to control the right platform (up - down).\n");
  printw("|3. Press Q to quit.                                        \n");
  printw("                          Player 1: %d | %d :Player 2\n", score_1,
         score_2);
  increase_score();
  borders(left_platform, right_platform);
}

void winner_is() {
    if (score_1 == 21) {
      mvprintw(30, 0, "Player 1 wins. Congrats!\n");
    } else if (score_2 == 21) {
      mvprintw(30, 0, "Player 2 wins. Congrats!\n");
    }
    mvprintw(31, 0, "Press any button");
    refresh();
    scanf("%x", &x);
}

int main() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  while (score_1 < 21 && score_2 < 21) {
    if (lift == 'a' || lift == 'z' || lift == 'k' || lift == 'm' ||
        lift == ' ') {
      render_page();

    } else {
      napms(100);
      win = coord_of_ball(left_platform, right_platform);
      render_page();
    }

    lift = getch();
    // УПРАВЛЕНИЕ ПЛАТФОРМАМИ
    if (lift == 'a' || lift == 'A') {
      if (left_platform == 3) {
        continue;
      } else {
        left_platform = left_platform - 1;
      }
    } else if (lift == 'z' || lift == 'Z') {
      if (left_platform == 23) {
        continue;
      } else {
        left_platform = left_platform + 1;
      }
    }
    if (lift == 'k' || lift == 'K') {
      if (right_platform == 3) {
        continue;
      } else {
        right_platform = right_platform - 1;
      }
    } else if (lift == 'm' || lift == 'M') {
      if (right_platform == 23) {
        continue;
      } else {
        right_platform = right_platform + 1;
      }
    }
    refresh();
  }
    winner_is();
  echo();
  nocbreak();
  endwin();
  return 0;
}

int borders(int left_platform, int right_platform) {
  for (int columns = 1; columns <= 25; ++columns) {
    for (int rows = 1; rows <= 80; ++rows) {
      border_x = '#';
      if (rows == 1) {
        printw("%c", border_y);
      } else if (rows == 80) {
        printw("%c\n", border_y);
      } else {
        if (columns == 1 || columns == 25) {
          printw("%c", border_x);
        } else if (columns > 1 && columns < 25) {
          if ((columns <= (left_platform + 1) &&
               columns >= (left_platform - 1)) &&
              (rows == 3)) {  // Первая платформа (первое фикс положение)
            printw("%c", paddle_1);
          } else if ((columns <= (right_platform + 1) &&
                      columns >= (right_platform - 1)) &&
                     (rows == 78)) {
            printw("%c", paddle_2);
          } else if (columns == y && rows == x) {  // Мячик
            printw("%c", ball);
          } else {
            border_x = ' ';
            printw("%c", border_x);
          }
        }
      }
    }
  }
  return 0;
}

int coord_of_ball(int left_platform, int right_platform) {
  if (x < 3) {
    x = 40;
    y = 13;
    if ((x + y) % 2 == 1) {
      x_speed = -x_speed, y_speed = y_speed;
    } else {
      x_speed = -x_speed, y_speed = -y_speed;
    }
    return 1;
  }
  if (x > 78) {
    x = 40;
    y = 13;
    if ((x + y) % 2 == 0) {
      x_speed = x_speed, y_speed = -y_speed;
    } else {
      x_speed = -x_speed, y_speed = y_speed;
    }
    return -1;
  }

  if (x == 4 && (left_platform - 2) <= y && y <= (left_platform + 2)) {
    x_speed = 1;
  } else if (x == 77 && (right_platform - 2) <= y &&
             y <= (right_platform + 2)) {
    x_speed = -1;
  }

  if (y <= 2) {
    y_speed = 1;
  } else if (y == 24) {
    y_speed = -1;
  }

  if (x_speed == 1 && y_speed == 1) {
    x++;
    y++;
  }
  if (x_speed == 1 && y_speed == -1) {
    x++;
    y--;
  }
  if (x_speed == -1 && y_speed == -1) {
    x--;
    y--;
  }
  if (x_speed == -1 && y_speed == 1) {
    x--;
    y++;
  }
  return 0;
}
