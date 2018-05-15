#include <iostream>
#include <LinkedList.h>
#include <str.h>


class TrieNode{
  TrieNode* child;
  // LinkedList<TrieNode*> childs;
  TrieNode* f;
  TrieNode(): child{nullptr}, f{nullptr} {}
};

class EndNode: public TrieNode{

  EndNode(): child{nullptr}, f{} {}
};

class StartNode: public Trienode{};

class Trie{
EndNode
StartNode

};



int main(){
  

  return 0;
}
