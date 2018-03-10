/** implementation of an LRU Cache**/
#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>

using namespace std;


class LRU
{
  list<int> Q;
  int max_size;
  unordered_map <int, pair<int,list<int>::iterator> > m;

public:
  LRU(int capacity);
  int get(int key);
  void put(int key,int value);
};
/**constructor**/
LRU::LRU(int capacity):max_size(capacity)
{
}

/**retrieve an element if it is present in the cache**/
int LRU::get(int key)
{
  if(m.find(key)!=m.end())
  {
    int value=m[key].first;
    list<int>::iterator it=m[key].second;
    Q.erase(it);
    Q.push_front(key);
    m[key].second=Q.begin();
    return value;
  }
  else
    return -1;
}
/**
    Insert an element into the cache if not already present.
    Update the value if present.
**/
void LRU::put(int key, int value)
{
  if(m.find(key)!=m.end())
    return;

  if(Q.size()==max_size)
  {
    int del_key=Q.back();
    Q.pop_back();
    m.erase(del_key);
  }
    Q.push_front(key);
    m[key]=make_pair(value,Q.begin());

}

int main()
{
  /**main function to test the member functions**/
  LRU cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  cout<<cache.get(1)<<endl;       // returns 1
  cache.put(3, 3);    // evicts key 2
  cout<<cache.get(2)<<endl;       // returns -1 (not found)
  cache.put(4, 4);    // evicts key 1
  cout<<cache.get(1)<<endl;       // returns -1 (not found)
  cout<<cache.get(3)<<endl;       // returns 3
  cout<<cache.get(4)<<endl;

  return 0;
}
