#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ncurses.h>

int head_x, head_y;
int body_x[50], body_y[50]; //int array käärmeen kropalle, kroppa max koko pelilaudan koko
int width = 50, height = 50, gameover = 0, size = 1;
void snake_board();
void input_check();
void move_snake();
void make_fruit();
void init_game(void); //käärmeen alustus pelipöydälle

int main (void) {
  init_game();

    while(!gameover) //peli loop pyörii, kunnes gameover
    {
      move_snake();
      snake_board();
      gameover=1;
      
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

void input_check(void)
{
  //Täällä chekataan käyttäjän näppäin painallukset
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