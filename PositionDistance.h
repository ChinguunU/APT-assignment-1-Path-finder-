// Code implemented by Chinguun Undrakh: s3774562

#ifndef COSC_ASS_ONE_POSITION
#define COSC_ASS_ONE_POSITION

#include "Types.h"

#define NOT_INITIAL     -1

class PositionDistance {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // x-co-ordinate
   int getX();

   // y-co-ordinate
   int getY();

   // Distance
   int getDistance();


   /*                             */
   /*      MY PUBLIC METHODS      */   
   /*                             */

   // Constructor
   PositionDistance(int x, int y);

   // Copy constructor
   PositionDistance(PositionDistance& positionDistanceToCopy);

   // Compare coordinates
   bool isSimilar(PositionDistance* positionToCompare);

   // Set distance
   void setDistance(int newDistance);

private:

   /*                               */
   /*     MY PRIVATE VARIABLES      */   
   /*                               */

   int x;
   int y;
   int distance;
};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef PositionDistance* PDPtr;

#endif // COSC_ASS_ONE_POSITION
