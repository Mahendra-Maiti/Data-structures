/*

      FAST is a data structure allowing the following operations in O(1) time:
      1. Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
      2. Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
      3. GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
      4. GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".

*/


#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>



class Bucket
{
public:
  int value;
  unordered_set<string> keys;
  Bucket* previous;
  Bucket* next;

  Bucket(int k)
  {
    value=k;
    previous=NULL;
    next=NULL;
  }
};


class FAST {

  Bucket* min_bucket;
  Bucket* max_bucket;
  unordered_map<string,int> keys;

  unordered_map<int,Bucket*> buckets;

  void delete_bucket(Bucket* BH)
  {
      //deletes bucket pointed by BH
      int val=BH->value;
      Bucket* prev=BH->previous;
      Bucket* nxt=BH->next;

      buckets.erase(val);

      if(prev==NULL)
      {
          min_bucket=nxt;
      }
      else
      {
          prev->next=nxt;
      }

      if(nxt==NULL)
          max_bucket=prev;
      else
          nxt->previous=prev;

  }

  Bucket* create_bucket(Bucket* nxt, Bucket* prev, int val)
  {
      //creates a new bucket corresponding to value val and links nxt and prev buckets
      Bucket* new_bucket=new Bucket(val);

      if(prev!=NULL)
      {

          prev->next=new_bucket;
          new_bucket->previous=prev;
      }
      else
      {
           //new_bucket is now min_bucket
          min_bucket=new_bucket;
      }

      if(nxt!=NULL)
      {
          nxt->previous=new_bucket;
          new_bucket->next=nxt;
      }
      else
      {
          //new_bucket is now max_bucket
          max_bucket=new_bucket;
      }

     buckets[val]=new_bucket;

     return new_bucket;

  }


public:

  FAST()
  {
        min_bucket=NULL;
        max_bucket=NULL;
   }


  void inc(string key)
  {
      if(keys.find(key)==keys.end())
      {
        //key not in FAST
        if(min_bucket!=NULL && min_bucket->value==1)
        {
            Bucket* BH=buckets[1];
            BH->keys.insert(key);
        }
        else
        {
            //create bucket corresponding to value 1
            Bucket* new_bucket=create_bucket(min_bucket,NULL,1);

            new_bucket->keys.insert(key);
        }

        keys[key]=1;
      }
      else
      {
        int index=keys[key];
        Bucket* BH=buckets[index];

        Bucket* nxt=BH->next;
        Bucket* prev=BH->previous;
        int BH_size=BH->keys.size();
        int newval=BH->value+1;
        //delete key from current bucket
        if(BH_size==1)
        {
            delete_bucket(BH);
        }
        else
        {
            BH->keys.erase(key);
        }

        //insert key into next bucket
        if(nxt==NULL || nxt->value>newval)
        {
          //next immediate bucket is not present. So insert next immediate bucket
          Bucket* new_bucket;
          if(BH_size==1)
            new_bucket=create_bucket(nxt,prev,newval);
          else
            new_bucket=create_bucket(nxt,BH,newval);

          new_bucket->keys.insert(key);
        }
        else
        {
          //next immediate bucket exists. So just insert key into this bucket
          nxt->keys.insert(key);
        }

         keys[key]=newval;              //update key's new bucket index

      }

  }


  void dec(string key)
  {
     if(keys.find(key)!=keys.end())
     {
       int index=keys[key];
       Bucket* BH=buckets[index];
       int val=BH->value;
       Bucket* prev=BH->previous;
       Bucket* nxt=BH->next;

       int newval=BH->value-1;
       int BH_size=BH->keys.size();

       //delete key from the current bucket
       if(BH_size==1)
       {
         //delete the entire bucket
        delete_bucket(BH);
      }
       else
       {
         BH->keys.erase(key);
       }

       //insert key into previous bucket;
       if(val!=1)
       {
         //removed key has to be inserted only if it's current value is greater than 1

         if(prev==NULL || prev->value<newval)
           {
             //previous immediate bucket is not present, hence has to be created
             Bucket* new_bucket;
             if(BH_size==1)
                new_bucket=create_bucket(nxt,prev,newval);
             else
                new_bucket=create_bucket(BH,prev,newval);

             new_bucket->keys.insert(key);

              }
          else
          {
           //previous immediate bucket is present. Insert key into this bucket.

             prev->keys.insert(key);
          }

           keys[key]=newval;   //update key's new bucket index;

       }
       else
           keys.erase(key);   //delete key if it's value was 1
     //else do nothing, since key is not present in FAST
    }
  }

  string getMaxKey()
  {
      if(max_bucket!=NULL)
      {
        auto it=max_bucket->keys.begin();
        return *it;
      }
      else
        return "";
  }


  string getMinKey()
  {
    if(min_bucket!=NULL)
    {
      auto it=min_bucket->keys.begin();
      return *it;
    }
    else
      return "";
  }
};
