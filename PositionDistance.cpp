// Code implemented by Chinguun Undrakh: s3774562

#include "PositionDistance.h"

int PositionDistance::getX() {
   return x;
}

int PositionDistance::getY() {
   return y;
}

int PositionDistance::getDistance() {
   return distance;
}


/*                                           */
/*       IMPLEMENTATION OF MY METHODS        */
/*                                           */


PositionDistance::PositionDistance(int x, int y) {
   this->x = x;
   this->y = y;
   this->distance = 0;
}

PositionDistance::PositionDistance(PositionDistance& positionDistanceToCopy) {
   this->x = positionDistanceToCopy.x;
   this->y = positionDistanceToCopy.y;
   this->distance = positionDistanceToCopy.distance;
}

bool PositionDistance::isSimilar(PositionDistance* positionToCompare) {
   bool isSimilar = false;
   
   if(x == positionToCompare->x && 
      y == positionToCompare->y) {
      
      isSimilar = true;
   } 
   
   return isSimilar;
}

void PositionDistance::setDistance(int newDistance) {
   this->distance = newDistance;
}
