#include "gthclient.h"

#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


int location_to_int(string location)
{
  vector<string> locations {  "a1", "b1", "c1", "d1", "e1",
                        "a2", "b2", "c2", "d2", "e2",
                        "a3", "b3", "c3", "d3", "e3",
                        "a4", "b4", "c4", "d4", "e4",
                        "a5", "b5", "c5", "d5", "e5",
                      };
  for(int i = 0; i < locations.size(); ++i)
  {
    if( locations[i] == location)
    {
      return i;
    }
  }
  return -1;
}

string int_to_location(int location)
{
  vector<string> locations {  "a1", "b1", "c1", "d1", "e1",
                        "a2", "b2", "c2", "d2", "e2",
                        "a3", "b3", "c3", "d3", "e3",
                        "a4", "b4", "c4", "d4", "e4",
                        "a5", "b5", "c5", "d5", "e5",
                      };
  for(int i = 0; i < locations.size(); ++i)
  {
    if( i == location)
    {
      return locations[i];
    }
  }
  return "failed";
}

int display_remaining_locations(vector<int> locations)
{
  for(auto i = locations.begin(); i != locations.end(); ++i)
  {
    cout << *i << ", " ;
  }

  return 0;
}


int main(){

  srand(time(0));

  char * current_location;
  char  local[] = "localhost";
  char * lh = local;

  set <int, greater<int> > locations;
  for(int j = 0; j < 25; ++j )
  {
    locations.insert(j);
  }


  char p[3] = ".p";
  char * pass = p;

  gth_start_game(GTH_WHO_BLACK, lh, 0);


  int rand_pick = 0;

  while(1)
  {
    try {
      rand_pick = rand()%25;
      if(locations.count(rand_pick))
      {

          locations.erase(rand_pick);
          current_location = const_cast <char *>( int_to_location(rand_pick).c_str() );

          if(gth_make_move(current_location) == 0)
          {
            gth_get_move(current_location);
            locations.erase(location_to_int(current_location));
          }
          else if(gth_make_move(current_location) == -1)
          {
            gth_make_move(pass);
            cout << pass << endl;
            gth_get_move(current_location);
            locations.erase(location_to_int(current_location));
          }
      }
    }
    catch (char * error)
    {
      cout << "Errors: " << error << endl;
    }
  }


  cout << "Team Black" << endl;

  return 0;
}
