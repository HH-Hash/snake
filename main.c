#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ncurses.h>

int score = 0;
int head_x, head_y;
int fruit_x, fruit_y;
int speed = 100000;
int body_x[50], body_y[50]; //int array käärmeen kropalle, kroppa max koko pelilaudan koko
int width = 50, height = 50;
int gameover = 0, worm_size = 1;
int dir = 1;
void snake_board(void);
void input_check(void);
char kb_press(void);
void move_snake(void);
void make_fruit(void);
void fruit_collision(void);
void init_game(void); //käärmeen alustus pelipöydälle

int main (void) {
  worm_size = 5;
    init_game();
    make_fruit();
    while(!gameover) //peli loop pyörii, kunnes gameover
    {
      snake_board();
      kb_press();
      input_check();
      move_snake();
      fruit_collision();
      gameover = 1;
    }
    return 0;
}

void snake_board(void)
{
  int i, j, k, no_body;
  for(j = 0; j <= height; j++) //ulompi loop kiertää korkeuden verran
  {
    for(i = 0; i <= width; i++) //sisempi loop kiertää leveyden verran
    {
      no_body=1;
      if(i == 0 || j == 0 || j == height || i == width) //rajojen chekkaus
      {
        printf("#"); //tulostetaan pelin seinät peli rajoille
        if(i == width) // lisää väli jollei ole oikean puoleisessa seinässä
        {
            if(i == 0 || j == 0 || j == height || i == width) //rajojen chekkaus
            {
                printf("#"); //tulostetaan pelin seinät peli rajoille
                if(i == width) // lisää väli jollei ole oikean puoleisessa seinässä
                {
                    printf(" "); //tulostetaan väli
                }
            } 
            else if(i == fruit_x && j == fruit_y) //tulostetaan hedelmä jos kordinaatit kohtaavat
            {
                printf("*"); //hedelmä
            }
            else if(i == head_x && j == head_y)
            {
                printf("Q"); //madon pää
            }
            else
            {
                printf(" "); //kierroksen lopuksi väli muuten tulostaa vasemman seinän viereen oikean
            }
        }
      }
      else if(i == head_x && j == head_y) //mikäli ruutu vastaa pään sijaintia tulosta pää
      {
        printf("Q");
      }
      else
      {
        for(k = 0; k < worm_size; k++) //tulostetaan käärmeen kroppa
        {
          if(i == body_x[k] && j == body_y[k]) //mikäli ruutu vastaa kroppaa tulosta kroppa
          {
          printf("o"); 
          no_body = 0; //vaihdetaan ei kroppaa epätodeksi
          }
        }
        if(no_body) //mikäli ei käärmeen kroppa tosi tulostaa tyhjää
        {
          printf(" ");
        }
      }
/*       else
      {
        printf(" "); //kierroksen lopuksi väli muuten tulostaa vasemman seinän viereen oikean
      } */
    }
  }
}

/**
Käsittelee näppäimen painalluksen sekä määrittää mihin suuntaan mato liikkuu.
Dir-muuttuja on numeerinen muuttuja, joka symboloi madon suuntaa.
Suunnat ovat 1,2,3 ja 4 eli ylös, oikea, alas ja vasen.
If-lohkot tarvitaan estämään vastakkaisten liikkeiden samanaikaisuus.
**/
void input_check(void)
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

char kb_press(void) {
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
void init_game(void) { 
    head_x = height / 2;
    head_y = width / 2;
}

void move_snake(void)
{
  int x1,x2,y1,y2,i;
  if(worm_size == 1)
  {
    body_x[0] = head_x; //määritellään pää arrayn ensimmäiseksi
    body_y[0] = head_y; //myös y suunnassa, kun peli alkaa
  }
  else 
  {
    x1 = head_x; //pään paikka x suunta
    y1 = head_y; //pään paikka y suunta
    for(i = 0; i < worm_size; i++) //pään paikasta kasvatetaan array worm_size verran
    {
      x2 = body_x[i];
      y2 = body_y[i];
      body_x[i] = x1;
      body_y[i] = y1;
      x1 = x2;
      y1 = y2;
    }
  }
}

//Luo uusia hedelmiä pelipöydälle
void make_fruit(void)
{
    resetfruit_x: fruit_x = rand() % 10;
    if(fruit_x == 0 || fruit_x == width)
        goto resetfruit_x;
    resetfruit_y: fruit_y = rand() % 10;
    if(fruit_y == 0 || fruit_y == height)
        goto resetfruit_y; 
}

void fruit_collision(void) {
    if(head_x == fruit_x && head_y == fruit_y) {
        score += 5;
        worm_size++;
        if(speed > 50000)
            speed -= 500;
            make_fruit();
    }
}

