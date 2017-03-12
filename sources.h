#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <signal.h>

typedef enum {HUMAN, STORM_ELF, FOREST_ELF, FURKIN} SPECIES;

void introduction();
char * getName();
SPECIES getSpecies();
struct char_details getPC();

void displayStats(struct char_details character);
char* speciesFetch(SPECIES species_enum);

struct char_details {
  char name[100];
  SPECIES species;
  int max_hp;
  int current_hp;
  int strength;
  int intel;
  int charm;
};
