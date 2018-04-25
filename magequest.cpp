#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale>

using namespace std;

/*
=========================
Design
=========================
The game will be a series of turn-based 'battles', 5 in total
The goal of the game is to have the player win every 'encounter'
A player wins an encounter by reducing all 'enemies' 'health points' to zero
The player loses, and must start over if his own health points are brought to zero
The players lost Health Points, and 'Magic Points', remain persistent through each fight
Using optimal actions against different enemy types to conserve these points is the key to winning

========================
    Attack Plan
========================
--Design the class enemy, and its resulting constructor. Test to see if objects in an array of enemy objects passed to another function can still have their
members edited.
--Constructor takes two strings, 'type', and 'name'. Every enemy object shall have a unique name string which will be displayed to player.
--Design a function, "createEncounter" that takes six strings, and creates an array of enemy objects with the constructor. The functions six string args will
be string firstType, string firstName, string secondType... etc.
--The function createEncounter will return a three length array of enemy, or pointer to arr[0]
--TEST TEST TEST to make sure the members of the array can be edited by other functions, use enemy object pointers as necessary
--Create Mage object. Will only need one global object, theMage, which represents the player.
--Create the display function, which accepts a Mage object, and an encounter object, and then displays relevant information to the player
--The relevant information being displayed are enemy objects whose bool isAlive is set to true, and their 'Health Points' int, and their 'name' string members
Make it look a little nice too, with like, -------------, and stuff. (give em the Ritz)
--Create the actionHandler function, which accepts a two strings, an 'action', which is an indentifier for the players valid actions, and a target
actionHandler also takes in the encounter. It iterates through the encounter array until it finds an enemy object whose name member matches the string 'target'
actionHandler then passes the necessary information, such as an enemy pointer, to the function according to 'action' string.
--Create the enemyAction function, which is similar to actionHandler, but takes an enemy object, and only one string 'action'. This will be called for each
enemy in an encounter when it is iterated through by a later function.
--Create enemyTurn function, which only needs to accept an 'encounter' array. This function calls enemyAction for each object in encounter. The object supplies
a pointer to itself, and supplies 'action' to enemyAction according to where the actionPoint to in enemy objects actionQue[aP]. The actionPointer of that 
enemy is added to by 1, unless it was at 3, in which case it resets to 0. Only objects whose bool member isAlive = true are called
--Create sample action, "Attack", which accepts an enemy object pointer, and then passes the int member of enemy object 'strength' to calculateDamage
calculateDamage returns a number within range of strength, which is passed to an integer named damage. damage is subtracted from theMage objects health
theMage checks to see if health is less than zero, but before then, attack has a side effect which displays this message, 
"enemyName attacks the Mage, dealing damage damage!"
--Create sample player action function, mageAttack, which accepts encounter array, and target from actionHandler. It passes the Mage objects 'strength' int member
as an argument to calculateDamage, and then subtracts the return value of that function from an enemy in the encounter array whose name string member matches the 
target string.
--Create function called getPlayerAction, which accepts no arguments, and asks the player for an action string. It will loop until given a valid action, which it 
then returns
--Create function called getTarget, which takes an encounter as an argument, and prompts the player to supply a string that matches a name from any of the objects
in the encounter array. It will keep asking for a target until it is given one that matches a name from encounter. It will give a list of valid targets every time
it is not supplied a valid target
--Create function called battle, which takes an encounter as an argument. It first uses display to display the current battle, then it creates two strings, action,
and target, which it fills by calling getPlayerAction, and getTarget. These strings and the encounter are passed as argument to actionHandler, which calls the
proper action. getTarget is skipped depending on action called, in which case, "mage" is passed to actionHandlers target param. Battle then calls enemyTurn
with its encounter param. Once this is done, it iterates through the encounter, checking each enemy objects isAlive, if all of them equal false, battle returns 
True, and then it checks theMage's isAlive member, and if it false, it returns false. Otherwise, it loops back to display.
--Design enemy types and encounters as desired!
*/

//-----Objects--------
class Mage{
  public:
  int health = 20;
  int defense = 0;
  int strength = 5;
  int magic = 30;
} theMage;

class enemy {
  public:
  int health;
  int defense;
  int strength;
  int magic;
  int aP;
  string actionQue[4];
  string type;
  enemy (string);
};
//--------------------

//-----Prototypes-----
string lowerCase(string);
int calculateDamage(int);
//--------------------

enemy::enemy (string type) {
  if (type == "goblin") {
    this->health = 3;
    this->defense = 0;
    this->strength = 3;
    this-> aP = 0;
    for (int i = 0;i < 4;i++) {
      this->actionQue[i] = "attack";
    }
  }
}

string lowerCase (string theStr) {
  std::locale loc;
  string newStr;
    std::string str = theStr;
    for (std::string::size_type i=0; i<str.length(); ++i)
      newStr += std::tolower(str[i],loc);
    return newStr;
}

int calculateDamage (int damage) {
  int rando = (rand() % 10);
  if (rando > -1 && rando < 2) return damage-2;
  else if (rando > 1 && rando < 4) return damage-1;
  else if (rando > 3 && rando < 6) return damage + 0;
  else if (rando > 5 && rando < 8) return damage + 1;
  else if (rando > 7 && rando < 10) return damage +2;
}

int main() {
  srand(time(NULL));
  
}