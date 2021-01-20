/*
Program Name: Final Project
Programmer: Chris Decker
Date Started: 12/12/2017
Purpose: to update a game using a grid and a indicatior to include borders, objects for the user to go around picking up, winning conditions, and availability for user to play again after winning
using inheritence and pointers to do it.
*/
//You can add or delete includes
#include <iostream>
#include <stdlib.h> //For system()
#include <conio.h> //For getche()
#include <time.h>
using namespace std;

//You can modify these numbers but don't delete these constants or this starting code will not work
const int MAX_HEIGHT = 20; //The height of the grid
const int MAX_WIDTH = 40; //The width of the grid

// DO NOT ALTER OR DELETE THIS CODE (START)!!!!!!!!!!!!!!!!!!!!!!!!!!!
/********************************************************************
 * Class: PickUpGame
 * Purpose: To store the grid and the current x and y position of the
 * user. Also has memeber functions to intialize the grid and print it.
 * Allows the user to move around the grid but provides no out of
 * bounds checking.
 ********************************************************************/
class PickUpGame
{
protected:
      char Screen[MAX_HEIGHT][MAX_WIDTH]; //The grid to print to the screen
      int xPos, yPos; //The current x and y position of the users cursor on the grid

public:
      //Constructor that will intialize the screen and x and y positions
      PickUpGame() : xPos(0), yPos(MAX_WIDTH - 1)
      {
           SetupScreen(); //Initalize the grid
      }

      //Initialize the screen with all '.' characters and set the intial user cursor position on the grid
      void SetupScreen()
      {
           for(int height = 0; height < MAX_HEIGHT; height++) {
                for(int width = 0; width < MAX_WIDTH; width++) {
                     Screen[height][width] = '.'; //Initialize each grid position
                }
           }
           Screen[xPos][yPos] = '<'; //Set the users initial cursor position
      }

      //Print the grid to the screen
      void Print()
      {
           for(int height = 0; height < MAX_HEIGHT; height++) {
                for(int width = 0; width < MAX_WIDTH; width++) {
                     cout << Screen[height][width]; //Print the character at this location in the grid
                }
                cout << endl; //After each row is printed, print a newline character
           }
      }

      //Take in user input to move around the grid
      void Move(char Direction)
      {
           switch(static_cast<int>(Direction)) //Don't know the ASCII characters for the arrow keys so use the ASCII numbers
           {
                case 72: //Up arrow
                     Screen[xPos][yPos] = ' '; //Wipe out the users current cursor
                     xPos--; //Move the users x position on the grid
                     Screen[xPos][yPos] = '^'; //Move the users cursor
                     break;
                case 80: //Down arrow
                     Screen[xPos][yPos] = ' ';
                     xPos++;
                     Screen[xPos][yPos] = 'V';
                     break;
                case 75: //Left arrow
                     Screen[xPos][yPos] = ' ';
                     yPos--;
                     Screen[xPos][yPos] = '<';
                     break;
                case 77: //Right arrow
                     Screen[xPos][yPos] = ' ';
                     yPos++;
                     Screen[xPos][yPos] = '>';
                     break;
           }
      }
};
// DO NOT ALTER OR DELETE THIS CODE (END)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
Class: update1
Purpose: to build upon class PickUpGame, creating a border for the grid, generating cookies for the user to find and pick up, 
create ways for the user to pick up the cookies, and printed victory message to user when all the cookies have been picked up.
*/
class update1 : public PickUpGame
	{
	protected: //protected, this part of the class can be modified only by the class it is in, and any child classes created in the future from it
		char yummy[MAX_HEIGHT][MAX_WIDTH]; //creates two dimensional array of type character named yummy with dimensions MAX_HIEGHT and MAX_WIDTH
		int xcookie, ycookie, cookie, grabbed; //sets up several integer variables
	public: //public part of the class, can be accessed from anywhere in the program
		void cookies() // creates a void function called cookies no parameters
		{
			grabbed = 0; //sets grabbed variable to value of 0
			cookie = rand() % 10+1; //grenerates a random amount of cookies bewteen 1 and 10
			for (int made = 0; made < cookie; made++) //for loop using int made set to zero, continues till while made is less than cookies, incriment made each time through
			{
				xcookie = rand() % MAX_HEIGHT ; //integer xcookie is equal to a random number more than 0 but up to the value of MAX_HEIGHT
				ycookie = rand() % MAX_WIDTH ; //integer ycookie is equal to a random number more then 0 but up to the value of MAX_WIDTH
				if (Screen[xcookie][ycookie] != '!') //checks to see if the character representing a cookie is already in the location randomly generated
				{
				Screen[xcookie][ycookie] = '!'; //sets yummylocation xcookie by ycookie to ! character
				}
				else //if the prevous statement is not true do this
					made--; //decrement made
			}
		}
		void Move(char Direction) //Move function with character Direction Parameter 
		{
			switch(static_cast<int>(Direction)) //starts a switch looking at the key entered into the Direction Character
			{
				case 72: //up arrow
					if (xPos-1 >= 0) //if after the movement xPos variable will be greater than or equal to 0 
					{
						Screen[xPos][yPos] = ' '; //sets Screen position xPos by yPos to  character
						xPos--; //decrement xPos
						picked(); ////calls picked function with no Parameters
						Screen[xPos][yPos] = '^'; //sets Screen position xPos by yPos to ^ character
						exiting(); //calls exiting function with no parameters
					}
					break; //breaks the current cycle
				case 80: //down arrow
					if (xPos+1 < MAX_HEIGHT) //if after the movement would xPos variable be less than MAX_HEIGHT variable
					{
						Screen[xPos][yPos] = ' '; //sets Screen position xPos by yPos to  character
						xPos++; //increment xPos
						picked();//calls picked function with no Parameters
						Screen[xPos][yPos] = 'V'; //sets Screen position xPos by yPos to V character
						exiting(); //calls exiting function with no parameters
					}
					break;
				case 75: //left arrow
					if (yPos-1 >= 0) //if after the movement would yPos varaiable be greater than or equal to 0
					{
						Screen[xPos][yPos] = ' ';//sets Screen position xPos by yPos to  character
						yPos--; //decrement yPos
						picked();//calls picked function with no Parameters
						Screen[xPos][yPos] = '<'; //sets Screen position xPos by yPos to < character
						exiting(); //calls exiting function with no parameters
					}
					break;
				case 77: //right arrow
					if (yPos+1 < MAX_WIDTH) //if after movement would yPos variable be less than MAX_WIDTH variable
					{
						Screen[xPos][yPos] = ' '; //sets Screen position xPos by yPos to  character
						yPos++; //increment yPos
						picked();//calls picked function with no Parameters
						Screen[xPos][yPos] = '>';  //sets Screen position xPos by yPos to > character
						exiting(); //calls exiting function with no parameters
					}
					break;
			}
		}
		int picked() //integer function picked with no parameters
		{
			if (Screen[xPos][yPos] == '!') //checks to see if Screen position xPos by yPos is equal to ! character
				grabbed++; //increment grabbed variable
			return(grabbed); //return grabbed variable
		}
		void message() //void function message with no parameters
		{
			cout << endl << "there are this many cookies on this grid: " << cookie << endl << "This is how many you have picked up: " << grabbed << endl; //prints message to keep track of how many cookies their are and how many have been picked up
		}
		void exiting() //void function exiting with no parameters
		{
				if (grabbed == cookie) // if variable is equal to variable cookie
			{
				system("cls"); //clear screen
				cout << endl << "Congradulations, You have won the game, see you later." << endl; //prints victory message
				Print(); //calls Print function
				message(); //calls message function
				system("pause"); //pauses system
				exit(0); //exits program with 0 error code
			}
		}
	};
//You can modify and change main()
/*
Function Name: Main
Purpose: to run the main part of the program and calls the other functions in the program
Parameters: none
type: integer
*/
int main()
{
      update1* Game = new update1; //Create a new game object and store it in a object pointer
	  srand(time(0)); //seeds random number generator with time
      char UserMove = ' '; //This is used to store the users input
	  Game->cookies(); //calls cookies function in Game instance of update1 class
      do { //starts do loop
           system("cls"); //Clear the screen before printing anything
           cout << "Welcome to the cookie game You will move to the cookies by using the arrow keys." << endl; //Program intro
           Game->Print(); //Print the grid out
           cout << "What direction would you like to move in? \n(Move using the arrow keys or type q to quit.) "; //Instructions to the user
           //UserMove = getche(); //Get one character from the user (some compilers have "getche()")
		   Game->message(); //calls function message from Game instance of update1 class no parameters
           UserMove = _getche(); //Get one character from the user (Visual Studio 2010 "_getche()" is the new version of "getche()")
           Game->Move(UserMove); //Process the users input
      } while(UserMove != 'Q' && UserMove != 'q'); //Keep running the program until the user types in a Q or q
      system("cls"); //Clear the screen
      cout << endl; //ends the line
      Game->Print(); //Print the final grid out to the user
      cout << endl; //ends the line
      return 0; //returns a value of zero
}
