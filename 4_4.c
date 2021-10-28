#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
// #include <dos.h>  - needed for Windows

#define GRIDSIZE 70

void runGame();
bool tick(int* position, void getDiff(int*));
void getTortoiseDiff(int* diff);
void getHareDiff(int* diff);
void getDebugDiff(int* diff);
void displayGrid(int tortoisePosition, int harePosition);

enum PLAYER { TORTOISE, HARE };


int main(void)
{
  runGame();
}





// Runs a single game
void runGame()
{
  int harePosition = 0, tortoisePosition = 0;
  bool gameOver = false, tortoiseWon = false;

  printf("BANG !!!!!\n");
  printf("AND THEY'RE OFF !!!!!\n");

  // While the game is running
  while (!gameOver)
  {

    // Update tortoise position
    gameOver = tick(&tortoisePosition, getTortoiseDiff);

    // Check game over for tortoise
    tortoiseWon = gameOver;

    // Update hare position and check game over for hare
    gameOver |= tick(&harePosition, getHareDiff);

    // Show grid and wait one second
    displayGrid(tortoisePosition, harePosition);
    sleep(1);
  }

  // Display who won
  if (tortoiseWon)
  {
    printf("TORTOISE WINS!!! YAY!!!\n");

  } else
  {
    printf("Hare wins. Yuch.\n");
  }
}





// Runs a single second of the game, in which it updates the position of
// either the tortoise or the hare
bool tick(int* position, void (*getDiff)(int*))
{

  // Update position
  (*getDiff)(position);

  // Hare/tortoise goes to a negative position
  if (*position < 0)
  {
    *position = 0;

  // Hare/tortoise goes over the board
  } else if (*position > GRIDSIZE - 1)
  {
    *position = GRIDSIZE - 1;
  }

  // Hare/tortoise wins
  if (*position == GRIDSIZE - 1) {
    return true;
  }

  // Neither won
  return false;
}





// Gets tortoise position
void getTortoiseDiff(int* pos)
{
  // Generate random int from 1 to 10
  srand(time(NULL));
  int num = rand() % 10;

  // Amount to update position by
  int diff;

  switch(num)
  {
    case 1: case 2:
      diff = -6; // slip
      break;
    case 3: case 4: case 5:
      diff = 1; // slow plod
      break;
    default:
      diff = 3; // fast plod
      break;
  }

  // Update position
  *pos += diff;
}





// Gets hare position
void getHareDiff(int* pos)
{
  // Generate random int from 1 to 10
  srand(time(NULL));
  int num = rand() % 10, diff;

  // Amount to update position by
  switch(num)
  {
    case 1: case 2:
      diff = 0; // sleep, 20%
      break;
    case 3: case 4:
      diff = 9; // big hop, 20%
      break;
    case 5:
      diff = -12; // big slip, 10%
      break;
    case 6: case 7:
      diff = -2; // small slip, 20%
      break;
    default:
      diff = 1; // small hop, 30%
      break;
  }

  // Update position
  *pos += diff;
}





// Debug function used to increment the hare's or tortoise's position
// by an arbitarily large amount (to check win conditions)
void getDebugDiff(int* pos)
{
  *pos += 30;
}





// Display the race grid
void displayGrid(int tortoisePosition, int harePosition)
{

  for (int i = 0; i < GRIDSIZE; i++)
  {

    // Check tortoise position
    if (i == tortoisePosition)
    {

      // Check for hare and tortoise at same position
      if (i == harePosition)
      {
        printf("OUCH!!!");

      } else
      {
        printf("T");
      }

    // Check hare position
    } else if (i == harePosition)
    {
      printf("H");

    // Blank position
    } else
    {
      printf("_");
    }

  }
  printf("\n");
}
