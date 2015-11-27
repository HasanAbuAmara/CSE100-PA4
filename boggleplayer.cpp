

#include "boggleplayer.h"
#include "boggleutil.h"
#include <algorithm>

void BogglePlayer::buildLexicon(const set<string>& word_list){
   delete lexicon;
   lexicon = new Lexicon();
   lexicon->build( word_list );
   lexiconMade = true;
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
   delete boardGraph;
   boardGraph = new BoardGraph();
   boardGraph->buildGraph( cols, rows, diceArray );
   boardSet = true;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
   if( !boardSet || !lexiconMade )
   {
      return false;
   }

   vector<string> minWords = lexicon->getValidWords( minimum_word_length );

   for( unsigned int i = 0; i < minWords.size(); i++ )
   {
      if( ( isOnBoard( minWords.at( i ) ) ).size() )
      {
         words->insert( minWords.at( i ) );
      }
   }

   return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
        return lexiconMade && lexicon->findWord( word_to_check );
}

bool BogglePlayer::isOnBoardHelper( vector<int>& pos, BoardNode* node, const string& word )
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
         if( !((*it)->wasVisited) && newWord.find( (*it)->diceStr ) == 0 )
         {
            couldBuildStr = isOnBoardHelper( pos, *it, newWord );
         }
      }

      if( !couldBuildStr )
      {
         pos.pop_back();
      }

      node->wasVisited = false;

      return couldBuildStr;
   }
}


vector<int> BogglePlayer::isOnBoard(const string& word) {
         string str = word;
         transform( str.begin(), str.end(), str.begin(), ::tolower );
         vector<int> result;
         result.clear();
         if( !boardSet )
         {
            return result;
         }

         vector<BoardNode*>::iterator it = boardGraph->boardNodes->begin();
         vector<BoardNode*>::iterator en = boardGraph->boardNodes->end();
         bool foundString = false;

         for( ; it != en; ++it )
         {
            if( foundString )
            {
               break;
            }
            if( str.find( (*it)->diceStr ) == 0 )
            {
                foundString = isOnBoardHelper( result, *it, str );
            }
         }

         return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
   delete boardGraph;
   setBoard( *rows, *cols, new_board );
}

