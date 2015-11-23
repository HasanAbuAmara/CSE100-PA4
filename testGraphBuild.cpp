#include <iostream>
#include <string>
#include "boggleutil.h"

using namespace std;

int main( int argc, char* argv[] )
{
   
   
   BoardGraph* graph = new BoardGraph();

   graph->buildGraph( 3, 3, a );

   delete graph;

   return 0;
}
