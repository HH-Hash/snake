#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>

int score = 0;
int head_x, head_y;
int fruit_x, fruit_y;
int speed = 100000;
int body_x[50], body_y[50]; //int array käärmeen kropalle, kroppa max koko pelilaudan koko
int width = 50, height = 50;
int gameover = 0, worm_size = 1;
int dir = 1;
void snake_board();
void input_check();
char kb_press();
void move_snake();
void make_fruit();
void fruit_collision();
void init_game(); //käärmeen alustus pelipöydälle
void game();
void gameover_check();

int main ()
{
    init_game();
    make_fruit();
    game();
    return 0;
}

void game()
{
    while(!gameover) {
        snake_board();
        input_check();
        move_snake();
        fruit_collision();
        gameover_check();
    }
    system("cls");
    printf("Your final Score : %5d", score);
}

void snake_board(void) {
    system("cls");
    int i,j,k,no_body;
    for(j=0;j<=height;j++) {
        for(i=0;i<=width;i++) {
            no_body=1;
            if(i==0||j==0||j==height||i==width)
                printf("#");
            else if(i==fruit_x&&j==fruit_y)
                printf("*");
            else if(i==head_x&&j==head_y)
                printf("Q");
            else {
                for(k=0;k<worm_size;k++) {
                    if(i==body_x[k] && j==body_y[k]) {
                        printf("+");
                        no_body=0;
                    }
                }
                if(no_body) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Scored : %5d\n",score);
    fflush(stdout); // Tarvitaan macOS:lle
}
/**
Käsittelee näppäimen painalluksen sekä määrittää mihin suuntaan mato liikkuu.
Dir-muuttuja on numeerinen muuttuja, joka symboloi madon suuntaa.
Suunnat ovat 1,2,3 ja 4 eli ylös, oikea, alas ja vasen.
If-lohkot tarvitaan estämään vastakkaisten liikkeiden samanaikaisuus.
**/
void input_check()
{    
    switch (kb_press()) 
    {
        case 'w':
            if(dir != 3)
                dir = 1;
            break;
        case 'd':
            if(dir != 4)
                dir = 2;
            break;
        case 's':
            if(dir != 1)
                dir = 3;
            break;
        case 'a':
            if(dir != 2)
                dir = 4;
    }
}

char kb_press() {
    initscr();
    timeout(50);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    char key = getch();
    endwin();
    return key;
}

//lisätään käärmeen pää keskelle pelipöytää
void init_game() { 
    head_x = height / 2;
    head_y = width / 2;
}

void move_snake()
{
  int x1, x2, y1, y2, i;
  if(worm_size == 1)
  {
    body_x[0] = head_x; //määritellään pää arrayn ensimmäiseksi
    body_y[0] = head_y; //myös y suunnassa, kun peli alkaa
  }
  else 
  {
    x1 = head_x; //pään paikka x suunta
    y1 = head_y; //pään paikka y suunta
    for(i = 0; i < worm_size; i++) //pään paikasta kasvatetaan array worm_worm_size verran
    {
      x2 = body_x[i];
      y2 = body_y[i];
      body_x[i] = x1;
      body_y[i] = y1;
      x1 = x2;
      y1 = y2;
    }
  }
  switch (dir) 
  {
    case 1:
      head_y--;
      break;
    case 2:
      head_x++;
      break;
    case 3:
      head_y++;
      break;
    case 4:
      head_x--;
      break;
  }
}

//Luo uusia hedelmiä pelipöydälle
void make_fruit()
{
    resetfruit_x: fruit_x = rand() % 20;
    if(fruit_x == 0 || fruit_x == width)
        goto resetfruit_x;
    resetfruit_y: fruit_y = rand() % 20;
    if(fruit_y == 0 || fruit_y == height)
        goto resetfruit_y; 
}

void fruit_collision()
{
    if(head_x == fruit_x && head_y == fruit_y) {
        score += 5;
        worm_size++;
        if(speed > 50000)
            speed -= 500;
            make_fruit();
    }
}

void gameover_check(void)
{
    int i;
    for(i=0;i<worm_size;i++)
    {
        if(head_x==body_x[i] && head_y==body_y[i])
        {
            gameover=1;
        }
    if(head_x==width||head_x==0||head_y==height||head_y==0)
    {
        gameover=1;
    }
}
