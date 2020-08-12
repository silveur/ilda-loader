/**
Main file for the Ilda reader. Creating a Max object able to read and decode ILDA frames
 */

#include <string>
#include <vector>
#include "ext.h"
#include "ext_obex.h"
#include "ext_path.h"
#include "../lib/IldaFrames.h"


using namespace std;

void *ildareader_class;



void ext_main(void *r)
{
  
  IldaFrames* reader = new IldaFrames();
  
  reader->openFile("/Users/silvereletellier/Downloads/LaserStuff/Import\ of\ ILDA\ frames\ in\ Max:MSP/Testfiles/ildatest.ild");
  
	return (0);
}
