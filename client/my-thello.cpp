#include "gthclient.h"

#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> 


using namespace std;

//Funtion to convert location label to int for processing
int location_to_int(string location, vector<string> labels)
{
  for(int i = 0; i < labels.size(); ++i)
  {
    if( labels[i] == location)
    {
      return i;
    }
  }
  return -1;
}
//Funtion to convert location int to label for processing
string int_to_location(int location, vector<string> labels)
{
  for(int i = 0; i < labels.size(); ++i)
  {
    if( i == location)
    {
      return labels[i];
    }
  }
  return "failed";
}
//Display current locations on game board for debugging 
int display_remaining_locations( set <int, greater<int> > locations)
{
  for(auto i = locations.begin(); i != locations.end(); ++i)
  {
    cout << *i << ", " ;
  }

  return 0;
}
//Determine if the chosen location is currently surrounded on all sides
bool illegal_move(int location,  set <int, greater<int> > locations)
{
  if( ( locations.count(location + 1) + locations.count(location - 1) + locations.count(location + 5) + locations.count(location - 5)) == 0 )
    return true;
  else
    return false;
}


int main(int argc, char** argv){
//Seed for random variable
  srand(time(0));
//Side assignment variable
  enum gth_who side;
//Labels for conversion when choosing move
  vector<string> labels {  "a1", "b1", "c1", "d1", "e1",
                        "a2", "b2", "c2", "d2", "e2",
                        "a3", "b3", "c3", "d3", "e3",
                        "a4", "b4", "c4", "d4", "e4",
                        "a5", "b5", "c5", "d5", "e5",
                      };
//Assign to start game as chossen side  
  if( strcmp(argv[1],"black") == 0 )
   side = GTH_WHO_BLACK;
  else
   side = GTH_WHO_WHITE;
//Pointer for server calls
  char * current_location;
  char  local[] = "localhost";
  char * lh = local;
  char p[3] = ".p";
  char * pass = p;
//Set of locations to know which places have been called
  set <int, greater<int> > locations;
  for(int j = 0; j < 25; ++j )
  {
    locations.insert(j);
  }
//Call to start game
  gth_start_game(side, lh, 0);

//Set random and weighted choices to 0 to start;
  int rand_pick = 0;
  int weighted_guess = 0;

  while(1)
  {
    //First round of moves, choose the center placement
      if( weighted_guess == 0)
        rand_pick = 12;
    //Otherwise choose positions in an X pattern
      else if(weighted_guess < 25)
        rand_pick = weighted_guess;
      else
    //Finally choose randomly and hope for the best
        rand_pick = rand()%25;
    //If the current move location hasn't been played and the move is legal
      if( locations.count(rand_pick) && !illegal_move(rand_pick, locations) )
      {
        //Remove pick from available choices
          locations.erase(rand_pick);
        //Set current choice to char pointer after converting to string location value
          current_location = const_cast <char *>( int_to_location(rand_pick, labels).c_str() );
        //If move is accepted by server
          if(gth_make_move(current_location) == 0)
          {
            //Get move from opponent and remove that from possible choices
            gth_get_move(current_location);
            locations.erase(location_to_int(current_location, labels));
          }
          else 
          {//Otherwise pass on turn and collect opponent's move
            gth_make_move(pass);
            gth_get_move(current_location);
            locations.erase(location_to_int(current_location, labels));
          }
      }
      //Increment weighted guess to next location in X pattern
      weighted_guess += 4;
  }
  


  cout << "Team Black" << endl;

  return 0;
}
