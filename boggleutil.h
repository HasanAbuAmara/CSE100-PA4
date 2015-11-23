

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <vector>
#include <map>
#include <string>

using namespace std;
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

class BoardNode
{
   friend class BogglePlayer;
   friend class BoardGraph;

   private:
      string diceStr;
      int index;
      bool wasVisited;
      vector<BoardNode*>* adjList;

   public:
      BoardNode( string& diceStr, int index );

      ~BoardNode();

      void addAdjacentBoardNode( BoardNode* node );
};

class BoardGraph
{
   friend class BogglePlayer;

   private:
      vector<BoardNode*>* boardNodes;
      //map<string, BoardNode*>* boardNodeOrganizer;

   public:
      BoardGraph();

      ~BoardGraph();

      vector<BoardNode*>* getNodesWithLetter( string& letter );

      void buildGraph( int width, int height, string** board );

};

class Lexicon
{
   private:
      int size;
      int capacity;
      vector<vector<string>* >* hashTable;
      int hash( const string& word );

   public:
      Lexicon();

      ~Lexicon();

     void build( const set<string>& word_list );

     bool findWord( const string& word );

     vector<string> getValidWords( unsigned int minLength );
};

#endif
