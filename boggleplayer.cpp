

#include "boggleplayer.h"
#include "boggleutil.h"

   BogglePlayer::BogglePlayer() : boardGraph( 0 ), boardSet( false ) {}

   BogglePlayer::~BogglePlayer()
   {
      delete boardGraph;
   }

void BogglePlayer::buildLexicon(const set<string>& word_list){
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
   boardGraph = new BoardGraph();
   boardGraph->buildGraph( cols, rows, diceArray );
   boardSet = true;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
        return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
        return true;
}

bool BogglePlayer::isOnBoardHelper( vector<int>& pos, BoardNode* node, string& word )
{
   if( node->diceStr == word )
   {
      pos.push_back( node->index );
      return true;
   }
   else
   {
      node->wasVisited = true;
      bool couldBuildStr = false;
      pos.push_back( node->index );
      
      vector<BoardNode*>::iterator it = node->adjList->begin();
      vector<BoardNode*>::iterator en = node->adjList->end();
      
      for( ; it != en; ++it )
      {
         if( !((*it)->wasVisited) && word.find( (*it)->diceStr ) == 0 )
         {
            couldBuildStr = couldBuildStr || isOnBoardHelper( pos, *it,
                           word.substr( node->diceStr.length(), word.length()-
                                        node->diceStr.length() ) );
         }
      }

      if( ! couldBuildStr )
      {
         pos.pop_back();
      }

      node->wasVisited = false;

      return couldBuildStr;
   }
}


vector<int> BogglePlayer::isOnBoard(const string& word) {
         vector<int> result;
         result.clear();
         vector<BoardNode*>::iterator it = boardGraph->boardNodes->begin();
         vector<BoardNode*>::iterator en = boardGraph->boardNodes->end();
         for( ; it != en; ++it )
         {
            if( word.find( (*it)->diceStr ) == 0 )
            {
                isOnBoardHelper( result, *it, word );
            }
         }
         return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

