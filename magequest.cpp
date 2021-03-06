#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale>
#include <vector>
using namespace std;

//-----Objects--------
class Mage{
  public:
  int health = 20;
  int defense = 0;
  int strength = 5;
  int magic = 30;
  bool isAlive = true;
  bool hasPotion = false;
  bool hasCloak = false;
} theMage;

class enemy {
  public:
  int health;
  int defense;
  int strength;
  int magic;
  int aP = 0;
  bool isAlive = true;
  string actionQue[4];
  string type;
  string name;
  enemy (string, string);
  enemy () {};
};
//--------------------

//-----Prototypes-----
void linePause();
void enemyTurn(enemy*);
bool battle(enemy*);
string getTarget(enemy*, string);
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
void golemGrumble(enemy*);
void rage(enemy*);
string artifactChoice();
bool windCloakCheck();
void quaff();
void hellFire(enemy*);
void nani();
void enemyHeal(enemy*);
void doom(enemy*);
void healBetween();
int stringCount(string);
string targetExtractor(string*);
void gerran0Magic(enemy*);
void enemyDefense(enemy*);
//--------------------

void gerran0Magic(enemy * gerran) {
  cout << "As Gerran raises his palms, his spell fizzles out.\n";
  cout << "\"Curse you, Mage! This isn't over, I can still gut you like a pig!\"\n";
  for (int i = 0;i < 4;i++) {
    gerran->actionQue[i] = "attack";
  }
}

void enemyDefense(enemy * caster) {
  if(caster->magic > 1) {
    caster->defense += 1;
    cout << "The air surrounding " << caster->name << " distorts. Defense raised\n";
    caster->magic -= 2;
  } else {
    gerran0Magic(caster);
  }
}

int stringCount(string count) {
  for (int i = 0;true;i++) {
    if (count[i] == '\0') return i;
  }
}

void linePause() {
  cout << "Press enter to continue";
  string a;
  getline(cin, a);
  return;
}

void enemyHeal(enemy * healer) {
  int heal = calculateDamage(6);
  if (healer->type == "goblinElite") {
    cout << healer->name << " quaffs a potion, restoring " << heal << " HP\n";
    healer->health += heal;
    if (healer->health > 15) healer->health = 15;
  } else {
    if (healer->magic > 1) {
      cout << "The dark wizard surrounds himself in a pale light, restoring " << heal << " HP\n";
      healer->health += heal;
      if (healer->health > 30) healer->health = 30;
      healer->magic -= 2;
    } else {
      gerran0Magic(healer);
    }
  }
}

void doom(enemy*doomer) {
  if (doomer->aP == 0) {
    cout << "The " << doomer->name << "'s eyes roll back into her head\n";
  } else if (doomer->aP == 1){
    cout << "The Doom Seer's mutterings begin to grow louder, and more hoarse\n";
  } else if (doomer->aP == 2) {
    cout << "The Doom Seer cackles, \"Soon.. master..\" she croaks\n";
  } else if (doomer->aP == 3) {
    cout << "The Doom Seer points her hagged old finger, indicating something behind the Mage. As he looks, he sees\n";
    cout << "the face of the death himself, and in the next moment, he's whisked from his mortal coil\n";
    theMage.isAlive = false;
  }
}

string artifactChoice() {
  cout << "You are ushered into the treasury. Your attendant bids their head, and asks you to take one artifact from the treasury\n";
  cout << "\n The light sword- A bane to the dark creatures that serve Gerran\n";
  cout << "\n The wind cloak- A cloak that allows you to move as nimbly as the wind itself\n";
  cout << "\n The mana potion- A powerful potion that can restore your mana in a pinch\n";
  cout << "\n Which shall you take?: ";
  string choice;
  while (true) {
    getline(cin, choice);
    choice = lowerCase(choice);
    if (choice == "light sword" || choice == "wind cloak" || choice == "mana potion") {
      if (choice == "light sword") {
        theMage.strength += 2;
        cout << "\"Excellent choice, may your enemies fall to your ATTACKS\", says the attendant\n";
        return choice;
      } else if (choice == "wind cloak") {
        theMage.hasCloak = true;
        cout << "\"Excellent choice, may your enemies not find you an easy target to pinpoint\", says the attendant\n";
        return choice;
      } else if (choice == "mana potion") {
        theMage.hasPotion = true;
        cout << "\"Excellent choice, may your wellspring of magic never run dry\", says the attendant\n";
        return choice;
      } else {
        cout << "That is not one of the artifacts, choose an artifact: ";
      }
    }
  }
}

void nani() {
  cout << "Beatrice's eyes widen, and she grunts, \"Why aren't you dead yet?! Damnit!\" \n";
}

bool windCloakCheck() {
  int check = (rand() % 5) + 1;
  if (check == 5 && (theMage.hasCloak == true)) {
    return true;
  } else return false;
}

void hellFire(enemy*caster) {
  int dam = calculateDamage(8);
  if (!windCloakCheck()) {
    if (caster->name == "Beatrice") {
      if(caster->magic < 3) {
        cout << "Beatrice cackles, and raises her palms, a puff of steam harmlessly streaming from her hands.\n";
      } else {
        cout << "Beatrice cackles, and raises her palms, a gout of hellfire springs forth, inflicting " << dam << " damage\n";
        theMage.health -= dam;
        caster->magic -= 3;
      }
    } else {
      if (caster->magic > 2) {
        cout << caster->name << " levels his palm, and a gout of hellfire springs forth, inflicting " << dam << " damage\n";
        caster->magic -= 3;
        theMage.health -= dam;
      } else {
        gerran0Magic(caster);
      }
    }
  } else {
    cout << "The Mage narrowly avoids a gout of hellfire\n";
    caster->magic -= 3;
  }
  if (theMage.health < 1) theMage.isAlive = false;
}

void quaff() {
  if (theMage.hasPotion) {
    cout << "The Mage quaffs the mana potion, rejuvenating his mana supply\n";
    theMage.magic += 10;
    if (theMage.magic > 30) theMage.magic = 30;
  } else {
    cout << "The Mage reaches for a potion, only to realize he has none!\n";
  }
}

void rage(enemy * enraged) {
  cout << enraged->name << " flies into a rage!\n";
  enraged->strength += 2;
}

void golemGrumble(enemy * golem) {
  cout << golem->name << " slowly moves into position to attack\n";
}

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
      if (victims[i].health < 1) {
        victims[i].isAlive = false;
        cout << victims[i].name << " perishes!\n";
      }
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
  if (target->health < 1) {
    target->isAlive = false;
    cout << target->name << " perishes!\n";
  }
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
    string target = targetExtractor(&action);
    if (action == "attack" || action == "mystic missile") {
      target = getTarget(theEncounter, target);
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
    string att, myst;
    for (int i = 0;i < 6;i++) {
      att += action[i];
    }
    for (int i = 0;i < 14;i++) {
      myst += action[i];
    }
    for (int i = 0;i < 6;i++) {
      if (action == validActions[i] || att == "attack" || myst == "mystic missile") {
        return action;
      }
    }
    cout << "Not a valid action\n";
  }
}

int stringToInt(string toCast) {
  if (stringCount(toCast) == 1) {
    char b = toCast[0];
    int a = b - '0';
    //int ia = a - '0';
    return a;
  }
  return 4;
}

string getTarget(enemy * anEncounter, string target) {
  for (int i = 0;i < 3;i++) {
    if ( (target == lowerCase(anEncounter[i].name) || stringToInt(target) == (i+1) )  && anEncounter[i].isAlive) {
      return anEncounter[i].name;
    }
  }
  cout << "Who do you target: ";
  while (true) {
    getline(cin, target);
    target = lowerCase(target);
    for (int i = 0;i < 3;i++) {
      if ( (target == lowerCase(anEncounter[i].name) || stringToInt(target) == (i+1) )  && anEncounter[i].isAlive) {
        return anEncounter[i].name;
      }
    }
    cout << "Not a valid target, these are the valid targets: ";
    for (int i = 0;i < 3;i++) {
      if (anEncounter[i].isAlive) {
        cout << anEncounter[i].name << ", ";
      }
    }
    cout << "\n";
  }
}

string targetExtractor(string * command) {
  string att, myst;
  string target;
  string action = *command;
  for (int i = 0;i < 6;i++) {
    att += action[i];
  }
  for (int i = 0;i < 14;i++) {
    myst += action[i];
  }
  if (att == "attack") {
    *command = "attack";
    for (int i = 7;action[i] != '\0';i++) {
      target += action[i];
    }
    return target;
  } else if (myst == "mystic missile") {
    *command = "mystic missile";
    for (int i = 15;action[i] != '\0';i++) {
      target += action[i];
    }
  }
  return target;
}

void attack(enemy * attacker) {
  int dam = calculateDamage(attacker->strength)-theMage.defense;
  if (dam < 0) dam = 0;
  if (windCloakCheck()) {
    cout << "As " << attacker->name << " moves to attack, the Mage nimbly sidesteps out of the way\n";
  } else {
    cout << attacker->name << " attacks The Mage, inflicting " << dam << " damage!\n";
    theMage.health -= dam;
  }
  if (theMage.health < 1) theMage.isAlive = false;
}

void enemyAction(string action, enemy * curEn) {
  if (action == "attack") {
    attack(curEn);
  } else if (action == "golemGrumble") {
    golemGrumble(curEn);
  } else if (action == "rage") {
    rage(curEn);
  } else if (action == "nani?!") {
    nani();
  } else if (action == "hellfire") {
    hellFire(curEn);
  } else if (action == "doom") {
    doom(curEn);
  } else if (action == "enemyHeal") {
    enemyHeal(curEn);
  } else if (action == "defenseUp") {
    enemyDefense(curEn);
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
    quaff();
  }
}

void mageAttack (enemy * tar) {
  int damage = calculateDamage(theMage.strength) - tar->defense;
  cout << "The mage strikes " << tar->name << ", inflicting "  << damage << " damage!\n";
  tar->health -= damage;
  if (tar->health < 1) {
    tar->isAlive = false;
    cout << tar->name << " perishes!\n";
  }
}

void displayBattle (enemy * encounter, Mage curMage) {
  cout << "-------------Enemies-------------\n";
  for (int i = 0;i < 3;i++) {
    if (encounter[i].isAlive) {
      cout << i+1 << ": " << encounter[i].name << " HP:" << encounter[i].health << "\n";
    }
  }
  cout << "-------------The Mage------------\n";
  cout << "HP:" << curMage.health << "/20 MP:" << curMage.magic << "/30\n";
  cout << "Actions: Attack | Quaff\n" << "Spells: Mystic missile: 2 | Heal: 1 | Defense Up: 1 | Fireball: 6\n";
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
    this->strength = 4;
    this->aP = 0;
    this->type = "weakGolem";
    this->name = name;
    this->actionQue[0] = "golemGrumble";
    this->actionQue[1] = "attack";
    this->actionQue[2] = "golemGrumble";
    this->actionQue[3] = "attack";
  } else if (type == "goblinRager") {
    this->health = 7;
    this->defense = 0;
    this->strength = 6;
    this->aP = 0;
    this->type = "goblinRager";
    this->name = name;
    this->actionQue[0] = "rage";
    for (int i = 1;i < 4;i++) {
      this->actionQue[i] = "attack";
    }
  }
  else if (type == "beatrice") {
    this->health = 30;
    this->defense = 0;
    this->strength = 1;
    this->aP = 0;
    this->type = "beatrice";
    this->name = name;
    this->magic = 9;
    for (int i = 0;i < 3;i++) {
      this->actionQue[i] = "hellfire";
    }
    this->actionQue[3] = "nani?!";
  } else if (type == "doomSeer") {
    this->health = 15;
    this->defense = 0;
    this->strength = 0;
    this->aP = 0;
    this->type = "doomSeer";
    this->name = name;
    for (int i = 0;i < 4;i++) {
      this->actionQue[i] = "doom";
    }
  } else if (type == "goblinElite") {
    this->health = 15;
    this->defense = 1;
    this->strength = 4;
    this->aP = 0;
    this->type = type;
    this->actionQue[0] = "attack";
    this->actionQue[1] = "enemyHeal";
    this->actionQue[2] = "rage";
    this->actionQue[3] = "attack";
    this->name = name;
  } else if (type == "strongGolem") {
    this->health = 25;
    this->defense = 3;
    this->strength = 5;
    this->aP = 0;
    this->type = "strongGolem";
    this->actionQue[0] = "golemGrumble";
    this->actionQue[1] = "attack";
    this->actionQue[2] = "golemGrumble";
    this->actionQue[3] = "attack";
    this->name = name;
  } else if (type == "darkWizard") {
    this->health = 30;
    this->defense = 0;
    this->strength = 5;
    this->aP = 0;
    this->magic = 20;
    this->type = "darkWizard";
    this->name = name;
    this->actionQue[0] = "defenseUp";
    this->actionQue[1] = "hellfire";
    this->actionQue[2] = "enemyHeal";
    this->actionQue[3] = "attack";
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
//IGNORE INCREDIBLY INELEGANT SOLUTION TO MEMORY PROBLEM
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

void healBetween() {
  cout << "Would you like to cast Heal/Quaff before your next fight? No to continue, or heal/quaff\n";
  string action;
  while (true) {
    getline(cin, action);
    action = lowerCase(action);
    if (action == "no" || action == "n" || action == "") return;
    if (action == "heal") heal();
    if (action == "quaff") quaff();
    cout << "HP:" << theMage.health << "/20 " << theMage.magic << "/30\n"; 
  }
}

bool partOne(enemy * enc) {
  cout << "The dark wizard Gerran has been terrorizing the countryside, and threatened to burn the puppy orphanage.\n";
  cout << "The king, in an attempt to save the puppies, has invited you, his court magician to his halls. The kings face\n";
  cout << "floods with relief as you enter.\n";
  cout << "\n\"Ah! My court wizard, excellent. I need you to stop this nefarious warlock, Gerran. I shall allow you\n";
  cout << "one mystic artifact from my treasury, for you to keep. May the gods smile on your journey, good Mage.\"\n";
  cout << "The king ushers his attendant to lead you to the treasury.\n";
  linePause();
  artifactChoice();
  cout << "----------------------------------------\n";
  cout << "Along the road on your journey, a pack of goblins assault you, the leader of the pack grins gleefully\n";
  cout << "\"Gerran sends his regards, Mage! Now die!\" it says as it charges you.\n";
  linePause();
  return battle(enc);
}

bool partTwo(enemy * enc) {
  theMage.defense = 0;
  cout << "As the Mage approaches Gerran's tower, he is confronted with a rickety bridge, guarded by Gerrans servants\n";
  cout << "The Mage prepares for battle\n";
  linePause();
  return battle(enc);
}

bool partThree(enemy * enc) {
  theMage.defense = 0;
  cout << "\nAcross the bridge, standing in front of Gerran tower, a demoness glowers at you\n";
  cout << "She smirks, \"No more games, Mage. I'm going to deliver your charred corpse to Gerran\"\n";
  cout << "She levels her palms, \"See you in hell!\"\n";
  linePause();
  return battle(enc);
}

bool partFour(enemy * enc) {
  theMage.defense = 0;
  cout << "As the Mage pushes into the tower, a voice greets him, \"So you have managed to defeat my apprentice, impressive.\n";
  cout << "I suspect you wont fare so well against my greatest servants however.. so this is our goodbye. I'll be sure to\n";
  cout << "feed your remains to your precious puppies before I crush them! Mwahahahahahahaha!\"\n\n";
  cout << "The Mage soon finds himself face to face against Gerrans elite monsters..\n";
  linePause();
  return battle(enc);
}

bool partFive(enemy * enc) {
  theMage.defense = 0;
  cout << "The mage climbs to the top of Gerrans tower, finding himself face to face with the man himself.\n";
  cout << "Gerran begins to slowly clap, \"Excellent work, Mage! You've exhausted yourself fighting my servants, and \n";
  cout << "now I get the satisfaction of destroying you. Its time I showed you how a true Magician fights!\"\n";
  linePause();
  return battle(enc);
}

int main() {
  string a;
  srand(time(NULL));
  enemy * encounter1 = createEncounter("goblin", "goblinA", "goblinRager", "Goblin Berserker", "goblin", "goblinC");
  enemy * encounter2 = createEncounter2("goblin", "goblin", "weakGolem", "Weak GolemA", "weakGolem", "Weak GolemB");
  enemy * encounter3 = createEncounter3("beatrice", "Beatrice", "", "", "", "");
  enemy * encounter4 = createEncounter4("doomSeer", "Doom Seer", "goblinElite", "Goblin Elite", "strongGolem", "Strong Golem");
  enemy * encounter5 = createEncounter5("darkWizard", "Gerran", "", "", "", "");
  if (partOne(encounter1)) {
    cout << "The Mage has defeated his opponents, the goblins!\n";
    linePause();
  } else {
    cout << "The Mage has perished!... as well as the puppies.";
    getline(cin, a);
    return 0;
  }
  healBetween();
  if (partTwo(encounter2)) {
    cout << "The Mage defeats Gerran's guards, and proceeds across the bridge\n";
    linePause();
  } else {
    cout << "The Mage has perished, in sight of Gerrans wicked tower!";
    getline(cin, a);
    return 0;
  }
  cout << "-----------------------------------------\n";
  healBetween();
  if (partThree(encounter3)) {
    cout << "After successfully defeating Beatrice, the Mage takes a moment to steel himself, before entering Gerran's tower\n";
    linePause();
  } else {
    cout << "The Mage perishes in Beatrice's hellfire.\n";
    getline(cin, a);
    return 0;
  }
  healBetween();
  if(partFour(encounter4)) {
    cout << "With Gerran's elite servants dispatched, the Mage prepares himself for his confrontation with Gerran\n";
  } else {
    cout << "The Mage at least made good puppy chow, before the puppies were incinerated...";
    getline(cin, a);
    return 0;
  }
  healBetween();
  if(partFive(encounter5)) {
    cout << "Congratulations on unlocking the special secret ending! Here's a cookie.\n";
    getline(cin, a);
  } else {
    cout << "Is this the end of the journey? Doomed to lose to Gerran? Perhaps the Mage could accept this fate for himself,\n";
    cout << "but... the thoughts of adorable unwanted puppies keep flooding his mind, and with a surge of vitality, the Mage\n";
    cout << "staggers back to his feet.\n";
    linePause();
    cout << "\"What?! You aren't dead yet?! Why you... fine. I'll just have to beat you down again!\"\n";
    linePause();
    theMage.isAlive = true;
    theMage.health = 10;
    theMage.magic = 15;
    if (battle(encounter5)) {
      cout << "After Gerran is defeated, peace returns to the lands. And more importantly, the puppy orphanage.";
      getline(cin, a);
    } else {
      cout << "Despite his most valiant efforts, the Mage perishes.";
      getline(cin, a);
    }
  }
}