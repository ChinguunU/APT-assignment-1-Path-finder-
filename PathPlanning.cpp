// Code implemented by Chinguun Undrakh: s3774562

#include "PathPlanning.h"

/*
* MILESTONE 2, 3
* In my implementations i have tried to minimise code duplication by using multiple private methods and arrays 
* for finding the next step such as leftRight[4], upDow[4]. Also, in implementing my methods such as initialPosition(), 
* getReachablePositions() and getPath() i have tried write the code in a way that it can be used multiple times to generate
* many different paths from different initial positions and goals in one run-time without crashing or causing memory leak. 
* This may have caused the methods mentioned above to be longer and slightly harder to understand due to multiple if statements. 
* However, i believe the advantages overthrow the disadvangtages because, by implementating it this way the program can not only 
* generate a path and reachable positions given one initial and goal positions but its methods can also be used for a game that 
* continuously generates a path depending on where the player is headed. All this achieved without having to change the code 
* is a win in my books.
* 
* One interesting approach i took in the implementations of class PathPlanning is that rather than generating all reachable 
* positions in method getReachablePositions() i have decided to generate the positions in initialPositions() method. Because, 
* this allows me control when to generate reachable positions. For example, if a user accidentally or purposefully tries to 
* generate reachable positions entering coordinates (8,2) into method initialPosition() twice in a row, then on the second time 
* rather than generating all reachable positions for (8,2) again by doing all the calculations the program would just 
* use the reacablePositions from the previous calculations (considering everything is happening in one run-time).
*
* The assignment was a lot of fun also learned a lot about how memory and pointers work. The only challenge worth mentioning 
* in this assignment was figuring out wether my code had memory leaks and how to fix it. After, browsing through google i 
* discovered a very useful and powerful tool called valgrind. By using this tool i was able to easily identify the flaws of my 
* code and fix it. Speaking of flaws i have found that the unit_tests.cpp contained potential memory leak in several places.
* (in main() did not use method delete_grid() nor deleted the data object also in run_unit_test() method it did not delete path)
* 
* Efficiency and quality advantages:
* - I have tried to use comparison operator != over < as it takes less steps to compute hence slightly faster.
* - Also ++i rather than i++ for the same reason stated above.
* - I have tried to use meaningfull variable names and methods to improve the quality and readability of my code.
* - Consistency in codeing style.
* - I have implemented each method carefully so that it wouldn't crash when inputs are wrong. (Would still safely run)
* - Memory is provided quiet efficiently and have only stored variabes in class PathPlanning that are necessary.
* Disadvantages:
* - Could have used less memory. For example, in method generateAllReahablePositions() rather than creating a new PDList object 
* (temporary list T) that kept track of which positions have already been checked i could have used a 2D bool array which stores
* true for every checked coordinate. This could potentially have used less memory.
*
* MILESTONE 4
* I have created a PDList constructor that allows the program to create a list that only has enough memory to store what is needed.
* By using this constructor in my implementation in PathPlanning i was able to effectively and efficiently allocate memory to 
* my PDList objects such as reachablePositions and path. Initially, in the constructor of PathPlanning i count all the '.' in the
* maze and initialise that value to the variable maxSizeOfLists. Which is later used in my code to create PDList objects with lists
* that only have enough memory to store (maxSizeOfLists) number of items. Moreover, the memory provided to PDList objects path and 
* reachablePositions are even smaller when possible(can be seen from implementation).
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {  
   this->rows = rows;
   this->cols = cols;  

   // Copying maze into map
   this->map = new char*[rows];
   for(int i = 0; i != rows; ++i) {
      
      this->map[i] = new char[cols];
      for(int ii = 0; ii != cols; ++ii) {

         this->map[i][ii] = maze[i][ii];
      }
   }

   // Counting how many '.' the maze has to calculate what the maximum list size should be 
   for(int i = 0; i != rows; ++i) {
      
      for(int ii = 0; ii != cols; ++ii) {
         
         if(map[i][ii] == PATH) {

            this->maxSizeOfLists++;
         }
      }
   }
}

PathPlanning::~PathPlanning() {
   
   // Delete grid/maze
   if (rows >= 0 && cols >= 0) {
      
      for (int i = 0; i != rows; ++i) {
         
         delete[] map[i];
      }
      
      delete[] map;
   }
   
   // Delete initialPos, reachablePositons list
   if(initialPos != nullptr) {
  
      delete initialPos;
      delete reachablePositions;
   }

   // Delete destinationPos
   if(destinationPos != nullptr) {
      
      delete destinationPos;
   }

   // Delete path
   if(path != nullptr) {
      
      delete path;
   }
}

void PathPlanning::initialPosition(int x, int y) {
   PDPtr position = new PositionDistance(x, y);
   
   if(x < cols && y < rows) {
      // If initialPos doesn't exist 
      if(initialPos != nullptr) {
         
         if(initialPos->isSimilar(position)) {
            
            // Deletes position if initialPos coordinates matches position coordinates
            delete position;
         } else {
            
            // Deletes reachablePositions, initialPos then re-initialises initialPos to position
            delete reachablePositions;
            delete initialPos;
            initialPos = position;
            generateAllReachablePositions();
         }
      } else {

         initialPos = position;
         generateAllReachablePositions();
      }
   }
}

PDList* PathPlanning::getReachablePositions() {
   PDList* copyOfList = nullptr;
   
   if(initialPos != nullptr) {   
      copyOfList = new PDList(*reachablePositions);
   }
 
   return copyOfList;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
   PDList* copyOfList = nullptr;

   // If initial position not provided program will do nothing
   if(initialPos != nullptr) {  
      
      // If destination position already exists
      if(destinationPos != nullptr) {
         
         // Deletes (destinationPos) and (path) then starts generating a new path
         delete destinationPos;
         delete path;
         generatePath(toX, toY);
         copyOfList = new PDList(*path);
      } else {
 
         generatePath(toX, toY);
         copyOfList = new PDList(*path);
      }
   }

   return copyOfList;
}


/*                                           */
/*       IMPLEMENTATION OF MY METHODS        */
/*                                           */

/*                                           */
/*               MILESTONE 2                 */
/*                                           */


void PathPlanning::generateAllReachablePositions() {
   
   // Declaring and allocating temporary list T and P
   PDList* listT = new PDList(maxSizeOfLists);
   PDList* listP = new PDList(maxSizeOfLists);
   listP->addBack(new PositionDistance(*(this->initialPos)));

   int x, y, distance;

   for(PDPtr coordinatesToCheck = initialPos; 
      coordinatesToCheck != nullptr; 
      coordinatesToCheck = findAbsentPositionCoordinate(listP, listT)) {
      
      // Examining coordinates above, below, to the right and to the left of coordinatesToCheck
      for(int i = 0; i != NUM_DIRECTIONS; ++i) {

         x = coordinatesToCheck->getX() + rightLeft[i];
         y = coordinatesToCheck->getY() + upDown[i];  
         distance = coordinatesToCheck->getDistance();
         
         addCoordinatesIfPath(x, y, distance, listP);
      }

      listT->addBack(new PositionDistance(*coordinatesToCheck));   
   }

   // Allocating memory and initialising values of reachablePositions list
   this->reachablePositions = new PDList(listP->size());
   for(int i = 1; i != listP->size(); ++i) {

      this->reachablePositions->addBack(new PositionDistance(*listP->get(i)));  
   }

   // Deleting temporary list T and P
   delete listT;
   delete listP;
}

PDPtr PathPlanning::findAbsentPositionCoordinate(PDList* list, PDList* listT) {
   PDPtr absentCoordinate = nullptr;
   
   if(list != nullptr) {

      for(int i = 0; absentCoordinate == nullptr && i != list->size(); ++i) {

         if(!listT->containsCoordinate(list->get(i))) {

            absentCoordinate = list->get(i);
         }
      }
   }
   
   return absentCoordinate; 
}

void PathPlanning::addCoordinatesIfPath(int x, int y, int distance, PDList* list) {
   PDPtr possiblePosCoordinate = new PositionDistance(x, y);
   bool added = false;

   if(!(list->containsCoordinate(possiblePosCoordinate))) {

      if(y < rows && x < cols && map[y][x] == PATH) {

         // If list doesnt contain the coordinates then set the distance and add it to the list
         possiblePosCoordinate->setDistance(distance + 1);
         list->addBack(possiblePosCoordinate);
         added = true;
      }
   } 
   
   if(!added) {

      delete possiblePosCoordinate;
   }
}

/*                                           */
/*               MILESTONE 3                 */
/*                                           */

void PathPlanning::generatePath(int toX, int toY) {
   PDList* listP = new PDList(*reachablePositions);
   listP->addBack(new PositionDistance(*initialPos));

   this->destinationPos = new PositionDistance(toX, toY);
   this->path = new PDList(listP->size());

   if(listP->containsCoordinate(destinationPos)) { 
      
      this->destinationPos->setDistance(listP->getThisPositionsDistance(destinationPos));
      this->path->addBack(new PositionDistance(*destinationPos));

      int x, y, distance;
      bool validStep;
      PDPtr newPosition = nullptr;
      PDPtr currentPosition = destinationPos;
      while(!path->containsCoordinate(initialPos)) {
          
         validStep = false;
         for(int i = 0; i != NUM_DIRECTIONS && !validStep; ++i) {

            x = currentPosition->getX() + rightLeft[i];
            y = currentPosition->getY() + upDown[i];
            distance = currentPosition->getDistance();

            newPosition = new PositionDistance(x, y);
            newPosition->setDistance(listP->getThisPositionsDistance(newPosition));

            validStep = 
               isValidStep(newPosition, distance, listP->containsCoordinate(newPosition));
            
            if(validStep) {
               
               path->addBack(newPosition);
               currentPosition = newPosition;
            } else {

               delete newPosition;
            }
         }
      }
   }

   delete listP; 
}

bool PathPlanning::isValidStep(PDPtr possibleCoordinates, int distance, bool contains) {
   bool choseDirection = false;

   if(contains) {

      if(possibleCoordinates->getDistance() < distance) {
         
         choseDirection = true;
      }
   } 
   
   return choseDirection;
}