// File:        pa3.cpp
// Author:      cs221 instructors
// Date:        2021-03-03
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets

#include "sqtree.h"

int main() {

  // read in image
  PNG orig;
  // orig.readFromFile("images/orig/small1.png");
  // orig.readFromFile("images/orig/small2.png");
  //orig.readFromFile("images/orig/pacman.png");
  // orig.readFromFile("images/orig/huckleberry_hound.png");
  // orig.readFromFile("images/orig/rocky.png");
  // orig.readFromFile("images/orig/rocky_bullwinkle.png");
  //orig.readFromFile("images/orig/colour.png");
 orig.readFromFile("images/orig/klee-flora-on-sand.png");
   //orig.readFromFile("images/orig/stanley-totem-poles.png");
  

  // use it to build a sqtree (try other tolerances)
  //SQtree t(orig,10.0);
  SQtree t(orig,20000);

  // copy the tree (to show you can)
   SQtree tCopy(t);

  // render the sqtree
  PNG pic = t.render();

  // write it out
  //pic.writeToFile("images/out/small1.png");
  // pic.writeToFile("images/out/small2.png");
  //pic.writeToFile("images/out/pacman.png");
  // pic.writeToFile("images/out/huckleberry_hound.png");
  // pic.writeToFile("images/out/rocky.png");
  // pic.writeToFile("images/out/rocky_bullwinkle.png");
  //pic.writeToFile("images/out/colour.png");
   pic.writeToFile("images/out/klee-flora-on-sand.png");
   //pic.writeToFile("images/out/stanley-totem-poles.png");
  return 0;
}
