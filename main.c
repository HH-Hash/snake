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
  int i,j,k;
  for(j=0;j<=height;j++) //ulompi loop kiertää korkeuden verran
  {
    for(i=0;i<=width;i++) //sisempi loop kiertää leveyden verran
    {
      if(i == 0 || j == 0 || j == height || i == width) //rajojen chekkaus
      {
        printf("*"); //tulostetaan pelin seinät peli rajoille
        if(i == width) // lisää väli jollei ole oikean puoleisessa seinässä
        {
          printf(" "); //tulostetaan väli
        }
      }
      else
      {
        printf(" "); //kierroksen lopuksi väli
      }
    }
    printf("\n"); //uusi rivi ja kierros uudestaan
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