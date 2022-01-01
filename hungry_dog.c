#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //for getch and system("cls")
#include <time.h>

#define N 10 //field's height
#define M 20 //field's width

int main() {
    char field[N][M];

    int x = 10, y = 5; //the pos of @
    int ax = rand() * 1.0 / RAND_MAX * (M - 2) + 1, //the apple pos
        ay = rand() * 1.0 / RAND_MAX * (N - 2) + 1;

    char key; //contains pressed key
    int eaten_apples = 0;
    
    srand(time(NULL));

    //set the field

    for (int i = 0; i < M; ++i) { //setting the top and bottom walls
        field[0][i] = '#';
        field[N - 1][i] = '#';
    }

    for (int i = 1; i < N - 1; ++i) { //setting the side walls
        field[i][0] = '#';
        for (int j = 1; j < M - 1; ++j) {
            field[i][j] = ' ';
        }
        field[i][M - 1] = '#';
    }

    do {
        if ((x == ax) && (y == ay)) { //if the positions are equal == the dog eats apple
            ax = rand() * 1.0 / RAND_MAX * (M - 2) + 1, //change apple pos
            ay = rand() * 1.0 / RAND_MAX * (N - 2) + 1;
            eaten_apples++;
        }
    
        system("cls");

        printf("Eaten apples: %d\n", eaten_apples);

        field[y][x] = '@';
        field[ay][ax] = '*';

        for (int i = 0; i < N; ++i) { //output field
            printf("%.*s\n", M, field[i]); //the basic %s outputs all matrix because it outputs everything before '\0' so 
                                        //I output it as M first symbols
        }

        field[y][x] = ' '; //forget about previous @ position

        key = getch();

        int cur_y = y, cur_x = x; //@ coordinates before the move

        if (key == 'w') y--; //change the @ position
        if (key == 's') y++;
        if (key == 'a') x--;
        if (key == 'd') x++;

        if (field[y][x] == '#') { //return the prev pos if the dog goes on walls
            y = cur_y;
            x = cur_x;
        }
    
    } while (key != 'e');

    return 0;
}
