#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ncurses.h>

int width=50, height=50;
void snake_board();
void input_check();
void move_snake();
void make_fruit();

int main (void) {
    
    snake_board();

    return 0;
}

void snake_board(void)
{
  int i,j,k,p;
  for(j=0;j<=height;j++)
  {
    for(i=0;i<=width;i++)
    {
      p=1;
      if(i == 0 || j == 0 || j == height || i == width)
      {
        printf("*");
      }
    }
    printf("\n");
  }

}

void input_check(void)
{
  //Täällä chekataan käyttäjän näppäin painallukset
}

void move_snake(void)
{

}

void make_fruit(void)
{
  //Tänne koodi, jolla tehdään ruokaa pelipöydälle
}