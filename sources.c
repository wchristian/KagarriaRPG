#include "sources.h"

//This is the introduction text that greets the player, explaing the back story and the game
void introduction(){
  printf("Welcome to the world of Kagarria.\n\n");
  printf("Kagarria exists in a point of potential war. The Humans are getting ready to advance and wipe out the Furkin. ");
  printf("The Furkin and bracing on the defense, trusting to their walls and warriors for their survival. ");
  printf("The Storm Elves watch warily, trusting neither side while he Forest Elves prepare to aid the Furkin in the war.\n");
  printf("\nYou are an adventurer starting in a human city. Your journey starts now...\n");
}

char * getName(){
  char * char_name = (char*)malloc(sizeof(char)*100);
  // printf("What is your name?\n");
  // fgets(char_name, 100, stdin);
  // printf("Your character has been named %s\n", char_name );
  // return char_name;

  char mesg[] = "Enter your character's name: ";
  int row, col;
  getmaxyx(stdscr, row, col);
  mvprintw(row/2, (col-strlen(mesg))/2, "%s", mesg);
  getstr(char_name);
  refresh();
  mvprintw(LINES - 2, 0, "You character's name has been set to %s", char_name);
  refresh();
  getchar();
  clear();
  refresh();
  return char_name;
}

SPECIES getSpecies(){
  // printf("There are four playable races in Kagarria.\n");
  // printf("Humans: Common but verstile. Start with +2 in all stats - 0\n");
  // printf("Storm Elves: From the snowy mountains. Start with +3 intel, ");
  // printf("+2 charm and +1 strength - 1\n");
  // printf("Forest Elves: From the deep dark forests. Start with +4 strength ");
  // printf(" and +3 intel - 2\n");
  // printf("Furkin: The animal races created for war. Start with +5 strength ");
  // printf("and +2 charm. - 3\n");

  char intro[] = "There are four playable races in Kagarria.";

  int row,col;
  // initscr();
  getmaxyx(stdscr, row, col);

  mvprintw(0,0,"%s",intro);
  mvprintw(3,0,"%s","Humans: Common but verstile. Start with +2 in all stats - 0\n");
  mvprintw(5,0,"%s","Storm Elves: From the snowy mountains. Start with +3 intel, ");
  mvprintw(6,0,"%s","+2 charm and +1 strength - 1\n");
  mvprintw(8,0,"%s","Forest Elves: From the deep dark forests. Start with +4 strength ");
  mvprintw(9,0,"%s"," and +3 intel - 2\n");
  mvprintw(11,0,"%s","Furkin: The animal races created for war. Start with +5 strength ");
  mvprintw(12,0,"%s","and +2 charm. - 3\n");

  SPECIES species = 0;
  char number[1];
  // fgets(number, 10, stdin);
  mvprintw(14,0,"Chose a species for your character by entering the number next to them.");
  refresh();
  number[0] = getchar();
  // int i = atoi(number);
  if (number[0] == '0' || number[0] == '1' || number[0] == '2' || number[0] == '3'){
    species =  number[0] - '0'; // This is here as number is read in as ASCII
  }
  else{
    mvprintw(16,0,"Incorrect input. Please enter a number between 0-3\n");
    refresh();
    species = getSpecies();
  }
  // printf("Species number in function is %d\n", species);
  clear();
  refresh();
  return species;
}

struct char_details getPC(){
  struct char_details this;
  int free_points = 1;
  int choice;

  char * name = getName();
  strcpy(this.name, name);
  this.species = 0;
  this.species = getSpecies();


  this.strength = 1;
  this.intel = 1;
  this.charm = 1;

  printf("Choose which skill you would like to level up:\n");
  printf("Strength: 0   Intel: 1    Charm: 2\n");

  while (free_points > 0){

      char* number = (char*)malloc(sizeof(char)*10);
      fgets(number, 10, stdin);
      // printf("input %s\n", number);
      if (number[0] == '0' || number[0] == '1' || number[0] == '2'){
        if (number[0] == '0'){
          this.strength++;
        }
        else if (number[0] == '1'){
          this.intel++;
        }
        else if (number[0] == '2'){
          this.charm++;
        }
        free_points--;
        printf("Strength: %d\nIntel: %d\nCharm: %d\n", this.strength,this.intel,this.charm);
        // printf("Intel: %d\n", this.intel);
        // printf("Charm: %d\n", this.charm);

      }
      else{
        printf("Please enter a number between 0-2 ");
        printf("You entered %s\n", number);
      }
  }
  this.max_hp = this.strength * 3; //hp max is 3 x strength
  this.current_hp = this.max_hp;

  return this;
}

void displayStats(struct char_details character){
  int row,col;
  // initscr();
  getmaxyx(stdscr, row, col);
  mvprintw((row/2)-3,(col-strlen(character.name))/2,"Character Name: %s",character.name);
  mvprintw((row/2)-2,(col-strlen(character.name))/2,"Species: %s", speciesFetch(character.species));
  mvprintw((row/2)-1,(col-strlen(character.name))/2,"Max HP: %d",character.max_hp);
  mvprintw((row/2),(col-strlen(character.name))/2,"Current HP: %d",character.current_hp);
  mvprintw((row/2)+1,(col-strlen(character.name))/2,"Strength: %d",character.strength);
  mvprintw((row/2)+2,(col-strlen(character.name))/2,"Intel: %d",character.intel);
  mvprintw((row/2)+3,(col-strlen(character.name))/2,"Charm: %d",character.charm);


  refresh();
  getchar();
  // endwin();
}

char* speciesFetch(SPECIES species_enum){
  char* species = (char*)malloc(sizeof(char)*15);
  switch(species_enum) {
    case HUMAN : strcpy(species, "Human");
    break;
    case STORM_ELF : strcpy(species, "Storm Elf");
    break;
    case FOREST_ELF : strcpy(species, "Forest Elf");
    break;
    case FURKIN : strcpy(species, "Furkin");
    break;
    default : strcpy(species, "Unknown");
    printw("Output %d", species_enum);
    break;
  }
  return species;
}
