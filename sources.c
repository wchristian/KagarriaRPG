#include "sources.h"

//This is the introduction text that greets the player, explaing the back story and the game
void introduction()
{
    printf( "Welcome to the world of Kagarria.\n\n" ); // why do multiple print calls if you could just do one and give it a block of text?
    printf( "Kagarria exists in a point of potential war. The Humans are getting ready to advance and wipe out the Furkin. " );
    printf( "The Furkin and bracing on the defense, trusting to their walls and warriors for their survival. " );
    printf( "The Storm Elves watch warily, trusting neither side while he Forest Elves prepare to aid the Furkin in the war.\n" );
    printf( "\nYou are an adventurer starting in a human city. Your journey starts now...\n" );
}

char * getName()
{
    char * char_name = ( char* )malloc( sizeof( char )*100 );
    char mesg[] = "Enter your character's name: ";
    int row, col;
    getmaxyx( stdscr, row, col );
    mvprintw( row/2, ( col-strlen( mesg ) )/2, "%s", mesg );
    getstr( char_name );
    refresh();
    mvprintw( LINES - 2, 0, "You character's name has been set to %s", char_name );
    refresh();
    getchar();
    clear();
    refresh();
    return char_name;
}

SPECIES getSpecies()
{
    screenStart();
    int row, col;
    getmaxyx( stdscr, row, col );

    // i don't think these need the templates
    mvprintw( 0, 0, "%s", "There are four playable races in Kagarria." );
    mvprintw( 3, 0, "%s", "Humans: Common but versatile. Start with +2 in all stats - 0" );
    mvprintw( 5, 0, "%s", "Storm Elves: From the snowy mountains. Start with +3 intel, " );
    mvprintw( 6, 0, "%s", "+2 charm and +1 strength - 1" );
    mvprintw( 8, 0, "%s", "Forest Elves: From the deep dark forests. Start with +4 strength " );
    mvprintw( 9, 0, "%s", " and +3 intel - 2" );
    mvprintw( 11, 0, "%s", "Furkin: The animal races created for war. Start with +5 strength " );
    mvprintw( 12, 0, "%s", "and +2 charm. - 3" );

    char number[1];
    mvprintw( 14, 0, "Chose a species for your character by entering the number next to them." );
    refresh();
    number[0] = getchar();
    SPECIES species = species_by_id( char number[1] );
    clear();
    refresh();
    return species;
}

SPECIES species_by_id( char number[1] )
{
    if( number[0] == '0' || number[0] == '1' || number[0] == '2' || number[0] == '3' )
        return number[0] - '0'; // This is here as number is read in as ASCII
    mvprintw( 16, 0, "Incorrect input. Please enter a number between 0-3" );
    refresh();
    return getSpecies();
}

struct char_details getPC()
{
    struct char_details this;

    int choice;

    char * name = getName();
    strcpy( this.name, name );
    this.species = 0;
    this.species = getSpecies();

    this = allocatePoints( this );

    return this;
}

struct char_details allocatePoints( struct char_details this )
{
    screenStart();
    int row, col;
    getmaxyx( stdscr, row, col );

    int free_points = 10;
    this.strength = 1;
    this.intel = 1;
    this.charm = 1;

    char number[1];

    mvprintw( 5, ( col/2 )- 20, "Choose which skill you would like to level up:" );
    mvprintw( 7, ( col/2 )- 14, "Strength: 0   Intel: 1    Charm: 2" );

    while( free_points > 0 ) {
        refresh();
        number[0] = getchar();
        if( number[0] == '0' || number[0] == '1' || number[0] == '2' ) {
            mvprintw( 13, 10, "Please enter a number between 0-2" );
            continue;
        }
        if( number[0] == '0' ) {  // there should be a way to access these by name
            this.strength++;
        } else if( number[0] == '1' ) {
            this.intel++;
        } else if( number[0] == '2' ) {
            this.charm++;
        }
        free_points--;
        mvprintw( 9, ( col/2 )-14, "Strength: %d   Intel: %d   Charm: %d", this.strength, this.intel, this.charm );
    }
    this.max_hp = this.strength * 3; //hp max is 3 x strength
    this.current_hp = this.max_hp;

    return this;
}

void displayStats( struct char_details character )
{
    int row, col;
    getmaxyx( stdscr, row, col );
    screenStart();

    // normally i'd try and mae this print thing into its own function, but again i dunno how to access members by name
    int half_row = row / 2;
    int offset = ( col-strlen( character.name ) ) / 2;
    mvprintw( half_row-3, offset, "Character Name: %s", character.name );
    mvprintw( half_row-2, offset, "Species: %s", speciesFetch( character.species ) );
    mvprintw( half_row-1, offset, "Max HP: %d", character.max_hp );
    mvprintw( half_row+0, offset, "Current HP: %d", character.current_hp );
    mvprintw( half_row+1, offset, "Strength: %d", character.strength );
    mvprintw( half_row+2, offset, "Intel: %d", character.intel );
    mvprintw( half_row+3, offset, "Charm: %d", character.charm );

    refresh();
    getchar();
}

char* speciesFetch( SPECIES species_enum )
{
    char* species = ( char* )malloc( sizeof( char )*15 );
    strcpy(
        species,
        species_enum == HUMAN ? "Human"
        : species_enum == STORM_ELF ? "Storm Elf"
        : species_enum == FOREST_ELF ? "Forest Elf"
        : species_enum == FURKIN ? "Furkin"
        : "Unknown"
    );
    if( strcmp( species, "Unknown" ) )
        printw( "Output %d", species_enum );
    return species;
}

void screenStart()
{
    clear();
    refresh();
}
