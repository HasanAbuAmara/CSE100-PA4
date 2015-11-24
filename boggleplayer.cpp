

#include "boggleplayer.h"
#include "boggleutil.h"

   BogglePlayer::BogglePlayer() : boardGraph( 0 ), boardSet( false ),
   lexicon( 0 ), lexiconMade( false ) {}

   BogglePlayer::~BogglePlayer()
   {
      delete boardGraph;
      delete lexicon;
   }

void BogglePlayer::buildLexicon(const set<string>& word_list){
   lexicon = new Lexicon();
   lexicon->build( word_list );
   lexiconMade = true;
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
        return lexiconMade && lexicon->findWord( word_to_check );
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
      
      string newWord = word.substr( node->diceStr.length(),
                                    word.length() - node->diceStr.length() );

      for( ; it != en; ++it )
      {
         if( couldBuildStr )
         {
            break;
         }
         if( !((*it)->wasVisited) && word.find( newWord ) == 0 )
         {
            couldBuildStr = couldBuildStr || isOnBoardHelper( pos, *it,
                                                              newWord );
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
         bool foundString = false;

         for( ; it != en; ++it )
         {
            if( foundString )
            {
               break;
            }
            if( word.find( (*it)->diceStr ) == 0 )
            {
                foundString = isOnBoardHelper( result, *it, word );
            }
         }

         return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

