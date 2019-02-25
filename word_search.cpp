/*
    Author: Mahendra Maiti
*/

/*
    Problem: Given a list of search words and a 2D grid of characters, search the grid and return starting positions in case 
    search words are found. For grid traversal, all 8 possible directions should be considered from a particular position. 
    A character in a grid can be used only once during construction of seach word.

    Possible approaches: 
        1. For every search word, DFS through grid to check if it exists: This requires repeated traversal through the grid
           which is pretty expensive.

        2. Use trie to cache all possible words that could be generated from the given grid:  This approach does not require
            repeated grid traversal. Once a trie is constructed, searching words entail only trie-search operations. This 
            approach is efficient in situations where the number of search words is huge.
    
*/

/*
    The following is a C++ implementation of a trie-based approach. The solution below contains a number of optimizations
    which significantly reduce the overall time complexity:

    1. To limit the length of traversal during DFS through the grid, a max_len variable is used to keep track of maximum length
        of a search word amongst the given. This is in assumption that the search words are known in advance.

    2. Another optimization to drastically reduce the number of possible words stored in the trie is to consider possible
        characters at any index in an arbitrary search string. By storing possible characters at any index in a search
        string, DFS traversals can be terminated earlier. For instance, if there is no search word beginning with 'X', then
        it is unnecessary to store words in the trie that start with 'X'. Similarly if there are no search words with a
        prefix "ANT", then all possible words with prefix "ANT", obtained during grid traversal can be discarded and subsequent
        traversal through that path can be abandoned. This step leads to huge performance gain.
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;


class node
{
    /*
        node class used for construction of trie.

        @children: possible character to node mappings for children. Compared to exising implementations which 
                   store a vector of length 26 in every node, this approach saves memory in case of a huge trie.
        @par: set of strings containing x,y coordinates of starting position in the grid.

        @terminating: boolean variable to indicate whether current node is an end of a string.
    */
    public:
        unordered_map<char,node*> children;
        unordered_set<string> par;
        bool terminating;
        node(){
            terminating=false;
        }
};

class trie{
    /*
        trie class providing word addition and search methods.

        @root: dummy node representing the root of the trie tree.
    */
    public:
        node* root;

        trie(){
            root=new node();
        }

        void add_word(string,int,int);
        string _exists(string&);

};

void trie::add_word(string word, int par_x, int par_y){
    /*
        Class method to add a given word to the trie.
        
        @word: input word to be inserted into the trie

        @par_x: starting x coordinate in the grid from which input word can be constructed.

        @par_y: starting y coordinate in the grid form which input word can be constructed.
    */

    cout<<"Adding "<<word<<endl;
    node* curr=root;
    for(int i=0;i<word.length();i++)
    {
        char temp=word[i];
        if(curr->children.find(temp)==curr->children.end()){
            node* new_node=new node();
            curr->children[temp]=new_node;
        }
        curr=curr->children[temp];
    }
    curr->terminating=true;
    curr->par.insert(to_string(par_x)+" "+to_string(par_y));        // add starting location 
}

string trie::_exists(string& word)
{
    /*
        Class method to search a given word in the trie.
        
        @word: input word to be searched in the trie.


        @returns: string containing the search word and space separated starting coordinates in case of a successful search.

    */
    string result="";
    node* curr=root;
    bool flag=true;

    for(int i=0;i<word.length();i++){
        char temp=word[i];
        if(curr->children.find(temp)==curr->children.end()){
            flag=false;
            break;
        }
        curr=curr->children[temp];
    }
    if(!flag || !curr->terminating || !word.length()){
        result=word+" "+to_string(-1)+" "+to_string(-1);    //word not found.
    }
    else
    {
        result=word+" "+ *(curr->par.begin());              //return any starting position in case of a successful search
    }

    return result;
}

void dfs(vector<vector<char>>& grid, int x, int y, int par_x, int par_y, trie& T, string word, int max_len,
                                             int step, vector<unordered_set<char>>& possible_chars){

    /*
        DFS through given grid.

        @grid: given 2D character grid.
        @x: current x-coordinate
        @y: current y-coordinate
        @par_x: x-coordinate of starting point
        @par_y: y-coordinate of starting point
        @T: Reference to trie object onto which words are to be inserted
        @word: current word generated during DFS through grid
        @max_len: maximum length of a search word, required for early termination of traversal
        @step: number of steps from starting position 
        @possible_chars: possible characters at any index in an arbitrary search string.
    */
    if(x<0 || x>=grid.size() || y<0 || y>=grid[0].size() || grid[x][y]==' ' 
                                        || max_len<=0 || possible_chars[step].find(grid[x][y])==possible_chars[step].end())
        return;

    char temp=grid[x][y];
    word=word+temp;

    T.add_word(word,par_x,par_y);       //add current generated word

    grid[x][y]=' ';
    max_len--;

    for(int i=-1;i<=1;i++)
    {
        for(int j=-1;j<=1;j++)
        {
            if(!(i==0 && j==0))
            {
                dfs(grid,x+i,y+j,par_x,par_y,T,word,max_len, step+1, possible_chars);   //traverse to next position.
            }
        }
    }

    grid[x][y]=temp;
}

void populate_trie(trie& T, vector<vector<char>>& grid, int max_len, vector<unordered_set<char>>& possible_chars){

    /*
        Function to populate trie with words.

        @T: Reference to trie object
        @grid: 2D character grid
        @max_len: maximum length of search word
        @possible_chars: stores all possible characters at any index in an arbitrary search string
    */
    int step=0;

    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if(possible_chars[0].find(grid[i][j])!=possible_chars[0].end()){
                dfs(grid,i,j,i,j,T,"",max_len,step,possible_chars);
            }
        }
    }
}



int main()
{
    vector<vector<char>> grid={
        {'A','B','C','D'},
        {'K','I','T','A'},
        {'A','N','D','Y'},
        {'M','A','I','D'},
        {'W','X','Y','Z'}
    };
    // vector<vector<char>> grid={
    //     {'A','B','C','D'},
    //     {'K','I','T','A'},
    //     {'A','N','D','Y'}
    // };


    // unordered_set<char> start_chars;
    
    vector<string> search_words={"ANDY","DAYDZ","XANIB","AIDDZY","DTNAAYXWM","AKAMWWM"};
    int max_len=numeric_limits<int>::min();

    for(auto word: search_words){
        max_len=max(max_len,(int)word.length());
        // start_chars.insert(word[0]);
    }
    vector<unordered_set<char>> possible_chars(max_len,unordered_set<char>());

    for(auto word: search_words){
        for(int i=0;i<word.length();i++){
            possible_chars[i].insert(word[i]);
        }
    }
    //vector<string> search_words={"ANDY"};
    vector<string> results;
    trie T;

    populate_trie(T,grid,max_len,possible_chars);

    for(auto word: search_words){
        results.emplace_back(T._exists(word));
    }
    
    cout<<"Search results: "<<"\n";
    for(auto result: results){
        cout<<result<<"\n";
    }

}