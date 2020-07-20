// Code implemented by Chinguun Undrakh: s3774562

#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "PositionDistance.h"
#include "PDList.h"
#include "Types.h"

#define PATH   '.'
#define NUM_DIRECTIONS   4

class PathPlanning {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise a with a given maze of size (x,y)
   PathPlanning(Grid maze, int rows, int cols);

   // Clean-up
   ~PathPlanning();

   // The initial position
   void initialPosition(int x, int y);

   // Method for Milestone 2
   // Return a DEEP COPY of the PDList of all position-distance's
   //    that the robot can reach
   PDList* getReachablePositions();


   // Method for Milestone 3
   // Get the path from the starting position to the given co-ordinate
   //    The path should be a DEEP COPY
   PDList* getPath(int toX, int toY);

private:
   
   /*                             */
   /*    MY PRIVATE VARIABLES     */   
   /*                             */

   Grid map;
   int rows;
   int cols;
   int maxSizeOfLists = 0;
   PDPtr initialPos = nullptr;
   PDPtr destinationPos = nullptr;
   PDList* reachablePositions = nullptr;
   PDList* path = nullptr;

   /*
   * Arrays for possible directions from a single position(rightleft[], upDown[])
   * Hence this specific combination will first check the left
   * then the right, then the bottom and lastly the upper coordinates 
   * of a x, y position coordinate
   */
   int rightLeft[NUM_DIRECTIONS] = {-1, 1, 0, 0};
   int upDown[NUM_DIRECTIONS] =    { 0, 0, 1,-1};

   /*                             */
   /*     MY PRIVATE METHODS      */   
   /*                             */

   // Generate all reachable positions from initial position
   void generateAllReachablePositions();

   // Add the coordinates to list P if it is the coordinates of a PATH
   void addCoordinatesIfPath(int x, int y, int distance, PDList* listP);

   // Find a position coordinate in listP that listT doesn't have
   PDPtr findAbsentPositionCoordinate(PDList* listP, PDList* listT);

   // Generates path given the input x and y destination coordinate
   void generatePath(int toX, int toY);

   // Returns true when coordinates can be the next step/path/position
   bool isValidStep(PDPtr newPosition, int distance, bool contains);

};

#endif // COSC_ASS_ONE_PATH_PLANNING
