#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <mmsystem.h>

#define width 65
#define height 25

typedef struct {
    int x, y;
    int w;
} TRacket;

typedef struct {
    float x, y;
    int ix, iy;

    float alpha;
    float speed;
} TBall;

char field[height][width];
TRacket racket;
TBall ball;

int hitCnt = 0;
int maxHitCnt = 0;

void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;

    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void initBall() {
    moveBall(2, 2);

    ball.alpha = -1;
    ball.speed = 0.5;
}

void putBall() {
    field[ball.iy][ball.ix] = '*';
}

void autoMoveBall() {
    if (ball.alpha < 0) {
        ball.alpha += M_PI * 2;
    }
    if (ball.alpha > M_PI * 2) {
        ball.alpha -= M_PI * 2;
    }

    TBall bl = ball;

    moveBall(ball.x + cos(ball.alpha) * ball.speed,
             ball.y + sin(ball.alpha) * ball.speed);

    if (field[ball.iy][ball.ix] == '#' || field[ball.iy][ball.ix] == '@') {

        if (field[ball.iy][ball.ix] == '@') {
            hitCnt++;
        }

        if (ball.ix != bl.ix && ball.iy != bl.iy) {
            if (field[bl.iy][ball.ix] == field[ball.iy][bl.ix]) {
                bl.alpha = bl.alpha + M_PI;
            } else {
                if (field[bl.iy][ball.ix] == '#') {
                    bl.alpha = (2 * M_PI - bl.alpha) + M_PI;
                } else {
                    bl.alpha = (2 * M_PI - bl.alpha);
                }
            }
        } else if (ball.iy == bl.iy) {
            bl.alpha = (2 * M_PI - bl.alpha) + M_PI;
        } else {
            bl.alpha = (2 * M_PI - bl.alpha);
        }

        ball = bl;
        autoMoveBall();
    }
}

void initRacket() {
    racket.w = 7;

    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}

void putRacket() {
    for (int i = racket.x; i < racket.x + racket.w; ++i) {
        field[racket.y][i] = '@';
    }
}

void moveRacket(int x) {
    racket.x = x;
    if (racket.x < 1) {
        racket.x = 1;
    }
    if (racket.x + racket.w >= width) {
        racket.x = width - 1 - racket.w;
    }
}

void init(int lvl) {
    for (int i = 0; i < width; ++i) {
        field[0][i] = '#';
    }

    strncpy(field[1], field[0], width);

    for (int i = 1; i < width - 1; ++i) {
        field[1][i] = ' ';
    }

    for (int i = 2; i < height; ++i) {
        strncpy(field[i], field[1], width);
    }

    if (lvl == 2) {
        for (int i = 20; i < 50; ++i) {
            field[10][i] = '#';
        }
    }

    if (lvl == 3) {
        for (int j = 1; j < 10; ++j) {
            for (int i = 1; i < 65; i += 7) {
                field[j][i] = '#';
            }
        }
    }

    if (lvl == 4) {
        for (int j = 1; j < 10; ++j) {
            for (int i = 1; i < 65; i += 7) {
                field[j][i] = '#';
            }
        }

        for (int i = 10; i < 60; ++i) {
            field[15][i] = '#';
        }
    }
}

void show(int lvl) {
    for (int i = 0; i < height; ++i) {
        printf("%.*s", width, field[i]);
        if (i == 1) {
            printf("    lvl %d    ", lvl);
        }
        if (i == 3) {
            printf("    hit %d    ", hitCnt);
        }
        if (i == 4) {
            printf("    max %d    ", maxHitCnt);
        }
        if (i < height - 1) {
            printf("\n");
        }
    }
}

void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showPreview(int lvl) {
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t    LEVEL %d", lvl);
    Sleep(1000);

    system("cls");
}

int main() {

    BOOL run = FALSE;
    int lvl = 1;

    initRacket();
    initBall();

    showPreview(lvl);

    do {
        setCur(0, 0);

        if (run) {
            autoMoveBall();
        }
        if (ball.iy > height) {
            run = FALSE;
            if (hitCnt > maxHitCnt) {
                maxHitCnt = hitCnt;
            }
            ball.alpha = -1;
            hitCnt = 0;
        }

        if (hitCnt > 3) {
            lvl++;

            run = FALSE;
            maxHitCnt = 0;
            hitCnt = 0;

            showPreview(lvl);
        }

        init(lvl);
        putRacket();
        putBall();
        show(lvl);

        if (GetKeyState('A') < 0) { //windows.h
            moveRacket(racket.x - 1);
        }
        if (GetKeyState('D') < 0) {
            moveRacket(racket.x + 1);
        }
        if (GetKeyState('W') < 0) {
            run = TRUE;
        }

        if (!run) {
            moveBall(racket.x + racket.w / 2, racket.y - 1);
        }
        Sleep(9);
    } while(GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}