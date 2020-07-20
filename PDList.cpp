// Code implemented by Chinguun Undrakh: s3774562

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>


PDList::PDList() {
   this->positions = new PDPtr[DEFAULT_SIZE];
}

PDList::~PDList() {
   clear();
}

int PDList::size() {
   return numPositions;
}

PDPtr PDList::get(int i) {
   PDPtr position = nullptr;
   
   if(i < numPositions) {
      
      position = positions[i];
   }

   return position;
}

void PDList::addBack(PDPtr position) {
   if(numPositions != maxListSize) {
      
      positions[numPositions] = position;
      numPositions++;
   } else {

      delete position;
   }
}

bool PDList::containsCoordinate(PDPtr position) {
   bool doesContain = false;
   
   for(int i = 0; doesContain == false && i != numPositions; ++i) {
      
      if(positions[i]->isSimilar(position)) {
         
         doesContain = true;
      }
   }

   return doesContain;
}

void PDList::clear() {
   for(int i = 0; i != numPositions; ++i) {
      
      delete positions[i];
   }

   delete[] positions;
}
 

/*                                           */
/*       IMPLEMENTATION OF MY METHODS        */
/*                                           */

 
PDList::PDList(int maxSize) {
   this->positions = new PDPtr[maxSize];
   this->maxListSize = maxSize;
}

PDList::PDList(PDList& listToCopy) {
   this->positions = new PDPtr[listToCopy.maxListSize];
   this->numPositions = listToCopy.numPositions;
   this->maxListSize = listToCopy.maxListSize;

   for(int i = 0; i != listToCopy.numPositions; ++i) {

      positions[i] = new PositionDistance(*(listToCopy.positions[i]));
   }
}

int PDList::getThisPositionsDistance(PDPtr position) {
   int distance = -1;
   if(containsCoordinate(position)) {
      for(int i = 0; i != numPositions && distance == -1; ++i) {
         
         if(positions[i]->isSimilar(position)) {

            distance = positions[i]->getDistance();
         }
      }
   }

   return distance;
}

