#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ncurses.h>

int head_x, head_y;
int body_x[50], body_y[50]; //int array käärmeen kropalle, kroppa max koko pelilaudan koko
int width = 50, height = 50;
int gameover = 0, size = 1;
int dir = 1;
void snake_board(void);
void input_check(void);
char kb_press(void);
void move_snake(void);
void make_fruit(void);
void init_game(void); //käärmeen alustus pelipöydälle

int main (void) {
    init_game();
    while(!gameover) //peli loop pyörii, kunnes gameover
    {
      move_snake();
      snake_board();
      gameover = 1;
      kb_press();
      input_check();
    }
    return 0;
}

void snake_board(void)
{
  int i,j,k;
  for(j = 0; j <= height; j++) //ulompi loop kiertää korkeuden verran
  {
    for(i = 0; i <= width; i++) //sisempi loop kiertää leveyden verran
    {
      if(i == 0 || j == 0 || j == height || i == width) //rajojen chekkaus
      {
        printf("#"); //tulostetaan pelin seinät peli rajoille
        if(i == width) // lisää väli jollei ole oikean puoleisessa seinässä
        {
          printf(" "); //tulostetaan väli
        }
      }
      else if(i == head_x && j == head_y)
      {
        printf("Q");
      }
      else
      {
        printf(" "); //kierroksen lopuksi väli muuten tulostaa vasemman seinän viereen oikean
      }
    }
    printf("\n"); //uusi rivi ja kierros uudestaan
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
  if(size==1)
  {
    body_x[0]=head_x; //määritellään pää arrayn ensimmäiseksi
    body_y[0]=head_y; //myös y suunnassa, kun peli alkaa
  }
  else 
  {
    x1 = head_x; //pään paikka x suunta
    y1 = head_y; //pään paikka y suunta
    for(i = 0; i < size;i++) //pään paikasta kasvatetaan array size verran
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

void make_fruit(void)
{
  //Tänne koodi, jolla tehdään ruokaa pelipöydälle
}
