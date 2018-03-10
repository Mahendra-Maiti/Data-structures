/** implementation of a custom hash map **/
#include <iostream>
#include <cmath>


using namespace std;
template <class K, class V>
class hash_value
{
public:
  K key;
  V value;
  hash_value():key(-1),value(-1){}
  hash_value(K key, V value):key(key),value(value)
  {}
};

template <class K, class V>
class hash_map
{
  int size;
  int capacity;

  hash_value<K,V>** map;
  hash_value<K,V>* dummy;
public:
  hash_map():size(0),capacity(5)
  {
      dummy=new hash_value<K,V>(-1,-1);
      map=new hash_value<K,V>*[capacity];

      for(int i=0;i<capacity;i++)
        map[i]=NULL;
  }

  /** generate hash code for a key **/
  int hash_code(K k)
  {
    return k%capacity;
  }

  /** expand the size of the hash map **/
  void reserve(int new_Size,bool copy)
  {
    hash_value<K,V>** newmap=new hash_value<K,V>* [new_Size];

    int old_size=capacity;
    capacity=new_Size;

    for(int i=0;i<old_size;i++)
    {
      if(map[i]!=NULL || map[i]->key!=-1)
      {
        int new_index=hash_code(map[i]->key);

        while(newmap[new_index]!=NULL)
        {
          new_index++;
          new_index=new_index%new_Size;
        }
        newmap[new_index]=map[i];
      }

    }

    map=newmap;
    capacity=new_Size;
  }
  /** insert <key,value> pair in the hash map **/
  void insert(K k, V v)
  {
      hash_value<K,V>* newval=new hash_value<K,V>(k,v);
      int index=hash_code(k);
      while(map[index]!=NULL && map[index]->key!=newval->key
                && map[index]->key!=-1)
      {
        index++;
        index=index%capacity;
      }

      if(map[index]==NULL || map[index]->key==-1)
      {
        size++;
      }
      map[index]=newval;
      if(size==capacity)
      {
        reserve(2*capacity,true);
      }

  }
  /** remove an element **/
  void remove(K k)
  {
      int index=hash_code(k);

      while(map[index]!=NULL)
      {
        if(map[index]->key==k)
        {
          map[index]=dummy;
          size--;
        }
        index++;
        index=index%capacity;

      }
  }
  /**search for a element**/
  V get(K k)
  {
      int index=hash_code(k);
      while(map[index]!=NULL)
      {
        if(map[index]->key==k)
          return map[index]->value;
        index++;
        index=index%capacity;
      }

      return dummy->value;
  }
/** return current size of the hash map**/
  int curr_size()
  {
    return size;
  }
/** return maximum size of the hash map **/
  int max_size()
  {
    return capacity;
  }
/** display the current contents of the hash map**/
  void disp()
  {
    cout<<endl<<"Hash_map contents: "<<endl;
    for(int i=0;i<capacity;i++)
    {
      if(map[i]!=NULL)
      {
        cout<<map[i]->key<<" "<<map[i]->value<<endl;
      }
    }
  }

};


int main()
{
  //testing the member functions
  hash_map<int,int> h;
  cout<<h.curr_size()<<" "<<h.max_size()<<endl;

  h.insert(1,2);
  h.insert(2,3);
  h.insert(3,4);
  cout<<endl<<h.max_size();
  h.insert(5,6);
  cout<<endl<<h.max_size();
  h.insert(7,8);
  cout<<endl<<h.max_size();
  h.insert(9,10);
  cout<<endl<<h.max_size();


//  h.disp();
  cout<<endl<<h.get(3)<<" "<<h.get(11)<<" "<<h.get(1)<<" "<<h.get(7)<<" "<<h.get(9);
  return 0;
}
