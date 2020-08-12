//
//  main.cpp
//  ild-test
//
//  Created by Silvere Letellier on 12/08/2020.
//  Copyright © 2020 Silvere Letellier. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "IldaFrames.h"

int main(int argc, const char * argv[]) {
  
  IldaFrames* reader = new IldaFrames();
  
  reader->openFile("/Users/silvereletellier/dev/ilda-loader/files/ildatest.ild");
  
  // insert code here...
  std::cout << "Hello, World!\n";
  return 0;
}
