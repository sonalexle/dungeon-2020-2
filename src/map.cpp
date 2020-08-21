//map generation
//todo: version of generateMap() which returns a single square room

#include "map.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <monster.hpp>

Map::Map(int difficulty) : difficulty_(difficulty) {
    rooms_.push_back(new Room); 
}

Room* Map::GetStartingRoom() {
    return rooms_.front();
}

//Runs when a map is constructed
void Map::map_init() {

    //Some preliminary parameters for how large the layout is and how many rooms are generated
    int nofRooms = 10 + difficulty_ * 2;

    //Init layout and starting room
    Room* map[9][9] = { {nullptr} };
    Room* start = new Room();
    map[5][5] = start;
    rooms_.push_back(start);

    //Create a random seed
    srand(time(nullptr));

    while (nofRooms > 0) {

        //Pick a random cell in array
        int x = rand() % 9;
        int y = rand() % 9;

        if(map[x][y] = nullptr) {

            //Where 1 is north, 2 is east, 3 is south, 4 is west
            std::list<int>neighbors;

            //Count how many neighbors the cell has
            if ( (x != 8) && map[x + 1][y] != nullptr) { neighbors.push_back(2);}
            if ( (x != 0) && map[x - 1][y] != nullptr) { neighbors.push_back(4);}
            if ( (y != 8) && map[x][y + 1] != nullptr) { neighbors.push_back(1);}
            if ( (y != 0) && map[x][y - 1] != nullptr) { neighbors.push_back(3);}

            //The maximum amount of neighbors can be tweaked to change the layout of the maps
            if(neighbors.size() > 1 && neighbors.size() < 3) {

                //All conditions are met, create a room
                // Room* room = Map::room_init();
                Room* room = new Room;
                map[x][y] = room;
                nofRooms--;

                //Setup connections for the new room
                for (int dir : neighbors) {
                    switch (dir) {

                        //For a northern connection c1 is on the northern wall and c2 on the southern wall (Coordinates are placeholder)
                        case 1: {
                            Connection* c1 = new Connection(50.0, 0.0);
                            Connection* c2 = new Connection(50.0, 100.0);

                            c1->SetRoom(room);
                            c1->connect(map[x][y + 1]);

                            c2->SetRoom(map[x][y + 1]);
                            c2->connect(room);
                        }
                        //For an eastern connection c1 is east and c2 west
                        case 2: {
                            Connection* c1 = new Connection(100.0, 50.0);
                            Connection* c2 = new Connection(0.0, 50.0);

                            c1->SetRoom(room);
                            c1->connect(map[x - 1][y]);

                            c2->SetRoom(map[x - 1][y]);
                            c2->connect(room);
                        }
                        //For a southern connection c1 is south and c2 north
                        case 3: {
                            Connection* c1 = new Connection(50.0, 100.0);
                            Connection* c2 = new Connection(50.0, 0.0);

                            c1->SetRoom(room);
                            c1->connect(map[x ][y - 1]);

                            c2->SetRoom(map[x][y] - 1);
                            c2->connect(room);
                        }
                        //For a western connection c1 is west and c2 east
                        case 4: {
                            Connection* c1 = new Connection(0.0, 50.0);
                            Connection* c2 = new Connection(100.0, 50.0);

                            c1->SetRoom(room);
                            c1->connect(map[x + 1][y]);

                            c2->SetRoom(map[x + 1][y]);
                            c2->connect(room);
                        }
                    }
                }
            }

            /*TODO: 
            -Logic for special rooms (e.g. boss room could be last room generated)
            -Find a way to output layout grid or have it as a class member
            */
        }
    }
}

/*TODO:
-Default constructs a room 
-Checks neighbors and creates connections
-Picks a file randomly from preconstructed room layouts and places entities
*/
Room* Map::room_init() {

    Room* room = new Room;
}