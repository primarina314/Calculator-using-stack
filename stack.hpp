#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Stack{
    private:
        int current;
        int size;
        T * array;

    public:
        Stack<T> (int _size = 16)
        {   
            current = -1;
            size = _size;
            array = new T[_size];
        }
        ~Stack()
        {
            delete[] array;
        }    

        bool isEmpty() const;
        bool isFull() const;
        T top() const;
        T pop();
        void push(const T& item);

        //additional function(not variable)
        int get_current() const;
        void show() const;
};

template <typename T>
bool Stack<T>::isEmpty() const{
    //TODO
    return current==-1;
}

template <typename T>
bool Stack<T>::isFull() const{
    //TODO
    return current==(size-1);
}

template <typename T>
T Stack<T>::top() const{
    //TODO
    return array[current];
}

template <typename T>
T Stack<T>::pop(){
    //TODO
    return array[current--];
}

template <typename T>
void Stack<T>::push(const T& item){
    //TODO
    if(isFull())
    {
        T* newArray = new T[size*2];
        size*=2;
        for(int i=0;i<=current;i++)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[++current] = item;
    return;
}

template<typename T>
int Stack<T>::get_current() const
{
    return current;
}

template<typename T>
void Stack<T>::show() const
{
    for(int i=0;i<=current;i++) cout<<array[i]<<" ";
    cout<<"\n";
}

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs);
float calculate(const string& line);