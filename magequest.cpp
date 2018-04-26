#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale>
#include <vector>
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

--Design spells and enemy types
*/

//-----Objects--------
class Mage{
  public:
  int health = 20;
  int defense = 0;
  int strength = 5;
  int magic = 30;
  bool isAlive = true;
} theMage;

class enemy {
  public:
  int health;
  int defense;
  int strength;
  int magic;
  int aP = 0;
  bool isAlive = true;
  string actionQue[3];
  string type;
  string name;
  enemy (string, string);
  enemy () {};
};
//--------------------

//-----Prototypes-----
void enemyTurn(enemy*);
bool battle(enemy*);
string getTarget(enemy*);
string getPlayerAction();
void attack(enemy*);
void enemyAction(string, enemy*);
void mageAttack(enemy*);
void actionHandler(string action, string target, enemy * enc);
void displayBattle(enemy*, Mage);
string lowerCase(string);
int calculateDamage(int);
enemy* createEncounter(string, string, string, string, string, string);
void mysticMissile(enemy*);
void heal();
void defenseUp();
void fireball(enemy*);
void quaff();
bool mpCheck(string);
void notEnoughMagic(string);
//--------------------

bool mpCheck(string spell) {
  if (spell == "fireball") {
    if (theMage.magic < 6) {
      return false;
    } else return true;
  }
  if (spell == "mystic missile") {
    if (theMage.magic < 2) {
      return false;
    } else return true;
  }
  if (spell == "heal" || spell == "defense up") {
    if (theMage.magic < 1) {
      return false;
    } else return true;
  }
}

void notEnoughMagic(string spell) {
  cout << "The Mage raises his hands to cast " << spell << ", but only a puff of smoke appears\n";
}

void fireball(enemy * victims) {
  cout << "With a sizzle, and a streak, a ball of fire flies from the Mage's hands, blowing up on every enemy\n";
  for (int i = 0;i < 3;i++) {
    if (victims[i].isAlive) {
      int dam = calculateDamage(5);
      cout << victims[i].name << " is engulfed in flames, taking " << dam << " damage!\n";
      victims[i].health -= dam;
      if (victims[i].health < 1) victims[i].isAlive = false;
    }
  }
  theMage.magic -= 6;
}

void defenseUp() {
  theMage.defense += 1;
  cout << "The air surrounding the Mage distorts, defense raised!\n";
  theMage.magic -= 1;
}

void heal() {
  int damageRestored = calculateDamage(7);
  theMage.health += damageRestored;
  if (theMage.health > 20) {
    theMage.health = 20;
  }
  cout << "A green light surrounds the Mage, restoring " << damageRestored << " health points!\n";
  theMage.magic -= 1;
}

void mysticMissile(enemy * target) {
  int damage = calculateDamage(9);
  cout << "A light emanates from the Mage's hands, striking " << target->name << ", and inflicting, "  << damage << " damage!\n";
  target->health -= damage;
  theMage.magic -= 2;
  if (target->health < 1) target->isAlive = false;
}

void enemyTurn(enemy * enemies) {
  for (int i = 0;i < 3;i++) {
    if (enemies[i].isAlive) {
      if (enemies[i].aP > 3) enemies[i].aP = 0;
      enemyAction(enemies[i].actionQue[enemies[i].aP], &enemies[i]);
      enemies[i].aP += 1;
    }
  }
}

bool battle(enemy * theEncounter) {
  bool battleRages = true;
  while (battleRages) {
    displayBattle(theEncounter, theMage);
    cout << "What action shall you take: ";
    string action = getPlayerAction();
    string target = "Mage";
    if (action == "attack" || action == "mystic missile") {
      cout << "Who do you target: ";
      target = getTarget(theEncounter);
    }
    cout << "\n-------------Action--------------\n";
    actionHandler(action, target, theEncounter);
    enemyTurn(theEncounter);
    cout << "---------------------------------\n\n";
    bool enemiesLive = false;
    for (int i = 0;i < 3;i++) {
      if (theEncounter[i].isAlive == true) {
        enemiesLive = true; 
      }
    }
    if (enemiesLive == false) {
      delete theEncounter;
      return true;
    } else if (theMage.isAlive == false) {
      return false;
    }
  }
}

string getPlayerAction() {
  string validActions[] = {"attack", "quaff", "mystic missile", "heal", "defense up", "fireball"};
  string action;
  while (true) {
    getline(cin, action);
    action = lowerCase(action);
    for (int i = 0;i < 6;i++) {
      if (action == validActions[i]) {
        return action;
      }
    }
    cout << "Not a valid action\n";
  }
}

string getTarget(enemy * anEncounter) {
  string target;
  while (true) {
    getline(cin, target);
    target = lowerCase(target);
    for (int i = 0;i < 3;i++) {
      if (target == lowerCase(anEncounter[i].name)) {
        return anEncounter[i].name;
      }
    }
    cout << "Not a valid target, these are the valid targets: ";
    for (int i = 0;i < 3;i++) {
      cout << anEncounter[i].name << ", ";
    }
    cout << "\n";
  }
}

void attack(enemy * attacker) {
  int dam = calculateDamage(attacker->strength)-theMage.defense;
  if (dam < 0) dam = 0;
  cout << attacker->name << " attacks The Mage, inflicting " << dam << " damage!\n";
  theMage.health -= dam;
  if (theMage.health < 1) theMage.isAlive = false;
}

void enemyAction(string action, enemy * curEn) {
  if (action == "attack") {
    attack(curEn);
  }
}

void actionHandler(string action, string target, enemy * enc) {
  enemy * targetEnemyPointer;
  for (int i = 0;i < 3;i++) {
    if (enc[i].name == target) {
      targetEnemyPointer = &enc[i];
    }
  }
  if (action == "attack") {
    mageAttack(targetEnemyPointer);
  } else if (action == "heal") {
    if (mpCheck(action)) {
      heal();
    } else notEnoughMagic(action); 
  } else if (action == "mystic missile") {
    if (mpCheck(action)) {
      mysticMissile(targetEnemyPointer);
    } else notEnoughMagic(action);
  } else if (action == "defense up") {
    if (mpCheck(action)) {
      defenseUp();
    } else notEnoughMagic(action);  
  } else if (action == "fireball") {
    if (mpCheck(action)) {
      fireball(enc);
    } else notEnoughMagic(action);
  } else if (action == "quaff") {
    //fill in latersees
  }
}

void mageAttack (enemy * tar) {
  int damage = calculateDamage(theMage.strength);
  cout << "The mage strikes " << tar->name << ", inflicting "  << damage << " damage!\n";
  tar->health -= (damage-tar->defense);
  if (tar->health < 1) tar->isAlive = false;
}

void displayBattle (enemy * encounter, Mage curMage) {
  cout << "-------------Enemies-------------\n";
  for (int i = 0;i < 3;i++) {
    if (encounter[i].isAlive) {
      cout << encounter[i].name << " HP:" << encounter[i].health << "\n";
    }
  }
  cout << "-------------The Mage------------\n";
  cout << "HP:" << curMage.health << "/20 MP:" << curMage.magic << "/30\n";
  cout << "Actions: Attack | Quaff\n" << "Spells: Mystic missile | Heal | Defense Up | Fireball\n";
}

enemy::enemy (string type, string name) {
  if (type == "") isAlive = false;
  if (type == "goblin") {
    this->health = 3;
    this->defense = 0;
    this->strength = 3;
    this->aP = 0;
    this->type = "goblin";
    this->name = name;
    for (int i = 0;i < 4;i++) {
      this->actionQue[i] = "attack";
    }
  } else if (type == "weakGolem") {
    this->health = 15;
    this->defense = 1;
    this->strength = 1;
    this->aP = 0;
    this->type = "weakGolem";
    this->name = name;
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
//IGNORE INCREDIBLE INELEGANT SOLUTION TO MEMORY PROBLEM
enemy* createEncounter(string firstType, string firstName, string secondType, string secondName, string thirdType, string thirdName) {
  static enemy encounter[3] = {
    enemy(firstType, firstName),
    enemy(secondType, secondName),
    enemy(thirdType, thirdName)
  };
  return encounter;
}

enemy* createEncounter2(string firstType, string firstName, string secondType, string secondName, string thirdType, string thirdName) {
  static enemy encounter[3] = {
    enemy(firstType, firstName),
    enemy(secondType, secondName),
    enemy(thirdType, thirdName)
  };
  return encounter;
}

enemy* createEncounter3(string firstType, string firstName, string secondType, string secondName, string thirdType, string thirdName) {
  static enemy encounter[3] = {
    enemy(firstType, firstName),
    enemy(secondType, secondName),
    enemy(thirdType, thirdName)
  };
  return encounter;
}

enemy* createEncounter4(string firstType, string firstName, string secondType, string secondName, string thirdType, string thirdName) {
  static enemy encounter[3] = {
    enemy(firstType, firstName),
    enemy(secondType, secondName),
    enemy(thirdType, thirdName)
  };
  return encounter;
}

enemy* createEncounter5(string firstType, string firstName, string secondType, string secondName, string thirdType, string thirdName) {
  static enemy encounter[3] = {
    enemy(firstType, firstName),
    enemy(secondType, secondName),
    enemy(thirdType, thirdName)
  };
  return encounter;
}

//THANKS

int main() {
  srand(time(NULL));
  enemy * encounter1 = createEncounter("goblin", "goblinA", "goblin", "goblinB", "goblin", "goblinC");
  enemy * encounter2 = createEncounter2("goblin", "goblinA", "weakGolem", "Weak Golem", "goblin", "goblinB");
  if (battle(encounter2)) {
    cout << "The mage is victorious!";
  } else {
    cout << "The mage has perished...";
  }
}