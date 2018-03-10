/** implementation of a custom vector **/
#include <iostream>
#include <assert.h>

using namespace std;

//implementing a custom vector
template <class T>
class vector
{
  T* v;
  int max_size;
  int curr_size;
  void reserve(int n, bool copy);
public:
  vector();
  vector(size_t length);
  vector(T init_val, size_t length);
  vector(vector<T>& arr);
  void push_back(T val);
  void pop_back();
  size_t size();
  T& back();
  T& front();
  T* begin();
  T* end();
  T& operator [](unsigned int index);
  vector<T>& operator =(vector<T>& arr);
};

template <class T>
void vector<T>::reserve(int n, bool copy)
{

    T* arr=new T[n];

    if(copy)
    {
      for(int i=0;i<curr_size;i++)
      {
        arr[i]=v[i];
      }
    }

    delete[] v;
    v=arr;
    max_size=n;
}

template <class T>
vector<T>::vector():curr_size(0),max_size(1)
{
    v=new T;
  //  cout<<"inside 0-arg constructor"<<endl;
}

template <class T>
vector<T>::vector(size_t length):curr_size(0)
{
  v=new T;
  reserve(length,false);
}

template <class T>
vector<T>::vector(T init_val, size_t length):curr_size(0)
{
    v=new T;
    reserve(length,false);
    for(int i=0;i<curr_size;i++)
    {
        v[i]=init_val;
    }
}

template <class T>
vector<T>::vector(vector<T>& arr):curr_size(0)
{
  //  cout<<"in copy"<<endl;

    v=new T[arr.size()];
    curr_size=0;
    max_size=arr.size();
    for(int i=0;i<arr.size();i++)
    {
      push_back(arr[i]);
    }

}

template <class T>
void vector<T>::push_back(T val)
{

  if(curr_size==max_size)
  {
      reserve(2*max_size,true);
  }
  curr_size++;
  v[curr_size-1]=val;
}

template <class T>
void vector<T>::pop_back()
{
    if(!curr_size)
      cout<<" empty vector"<<endl;
    else
    {
      curr_size--;
    }
}

template <class T>
size_t vector<T>::size()
{
  return curr_size;
}

template <class T>
T& vector<T>::back()
{
  return v[curr_size-1];
}

template <class T>
T& vector<T>::front()
{
    return v[0];
}

template <class T>
T& vector<T>::operator [](unsigned int index)
{
  assert(index>=0 && index<curr_size);
  return v[index];
}

template <class T>
vector<T>& vector<T>::operator =(vector<T>& arr)
{
  delete[] v;
//  cout<<"inside copy assignment"<<endl;
  cout<<size();
  v=new T[arr.size()];

  for(int i=0;i<arr.size();i++)
    v[i]=arr[i];

    return *this;

}

template <class T>
T* vector<T>::begin()
{
  return v;
}

template <class T>
T* vector<T>::end()
{
    return v+curr_size;
}



int main()
{

  //testing the class member functions.
  vector<int> v1;
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  v1.push_back(5);
  v1.push_back(6);
  cout<<endl;
  for(int i=0;i<v1.size();i++)
    cout<<v1[i]<<" ";

  v1.pop_back();
    cout<<endl;
    for(int i=0;i<v1.size();i++)
      cout<<v1[i]<<" ";

  cout<<endl<<v1.front()<<" "<<v1.back();

  vector<int> v2(v1);

  vector<int> v3;
  v3=v2;
  cout<<endl;

  for(auto x:v2)
    cout<<x<<" ";
  return 0;


}
