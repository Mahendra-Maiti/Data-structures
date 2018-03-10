/** implementation of a trie **/
#include <iostream>
#include <string>
#include <vector>

#define ALPHABET_SIZE 26

using namespace std;

class Trie {
    class Trie* children[26];
    bool isEnd;
public:
    Trie()
     {
            for(int i=0;i<26;i++)
               children[i]=NULL;

            isEnd=false;

    }
    /**insert words into the trie **/
    void insert(string word)
     {
        Trie* curr=this;

        for(int i=0;i<word.length();i++)
        {
            int offset=word[i]-'a';

            if(!curr->children[offset])
            curr->children[offset]=new Trie();

            curr=curr->children[offset];
          }
          curr->isEnd=true;

      }

    /** Returns if the word is in the trie. */
    bool search(string word)
     {
        Trie* curr=this;
        for(int i=0;i<word.length();i++)
        {
          int offset=word[i]-'a';
          if(curr->children[offset]==NULL)
            return false;
            curr=curr->children[offset];
          }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* curr=this;

        for(int i=0;i<prefix.length();i++)
        {
            int offset=word[i]-'a';

            if(!curr->children[offset])
                return false;

            curr=curr->children[offset];
        }

        return true;

    }
};



int main()
{
  string keys[] = {"the", "a", "there",
                      "answer", "any", "by",
                       "bye", "their" };
      int n = sizeof(keys)/sizeof(keys[0]);

      struct Trie *root = new Trie();

      // Construct trie
      for (int i = 0; i < n; i++)
          root->insert(root, keys[i]);

      // Search for different keys
      root->search(root, "the")? cout << "Yes\n" :
                           cout << "No\n";
      root->search(root, "these")? cout << "Yes\n" :
                             cout << "No\n";
      return 0;
}
