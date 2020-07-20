// Code implemented by Chinguun Undrakh: s3774562

#ifndef COSC_ASS_ONE_POSITION_LIST
#define COSC_ASS_ONE_POSITION_LIST

#include "PositionDistance.h"
#include "Types.h"

#define DEFAULT_SIZE    100

class PDList {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Create a New Empty List
   PDList();

   // Clean-up the list
   ~PDList();

   // Number of items in the list
   int size();

   // Get a pointer to the position-distance at index i
   PDPtr get(int i);

   // Add a position-distance (as a pointer) to the list
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance is removed from the list
   void addBack(PDPtr position);

   // Checks if the list contains a position-distance with the same co-ordinate
   //    as the given position.
   bool containsCoordinate(PDPtr position);

   // Remove everything from the list
   // Don't forget to clean-up the memory!
   void clear();


   /*                             */
   /*      MY PUBLIC METHODS      */   
   /*                             */

   // Constructor that allows to customize list size
   PDList(int maxSize);

   // Copy constructor
   PDList(PDList& listToCopy);

   // Returns a pointer of the position in the list that has coordinates x, y
   int getThisPositionsDistance(PDPtr position);

private:
   
   /*                               */
   /*     MY PRIVATE VARIABLES      */   
   /*                               */

   PDPtr*   positions;
   int      numPositions = 0;
   int      maxListSize = DEFAULT_SIZE;
};

#endif // COSC_ASS_ONE_POSITION_LIST
