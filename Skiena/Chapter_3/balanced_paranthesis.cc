#include <iostream>
#include <stack> 
#include <string.h>
using namespace std;

template<typename T>
class Stack {
    int top;
public:
    int array[10000];
    Stack() 
    {
        top = -1;
    }

    bool push(T x);

    int pop();

    bool isEmpty();
};

template<typename T>
bool Stack<T>::push(T x)
{
    if (top == 10000)
    {
        cout <<"Stack overflow\n";
        return false;
    }
    top++;
    array[top] = x;
}

template<typename T>
int Stack<T>::pop()
{
    if (top < 0)
    {
       cout <<"Stack underflow";
       return 0;
    }

    top--;
    int ret =  array[top];
    return ret;
}

template<typename T>
bool Stack<T>::isEmpty()
{
    cout << top<<endl;
    if (top < 0)
    {
        return true;
    }
    else
        return false;
}

int main(int argc, char** argv)
{
    Stack<char> mystack = Stack<char>();

    char* str = argv[1];   

    for (int i=0; i<strlen(str); i++)
    {
        if (str[i] == '(')
        {
            cout << "pushing " << str[i] << endl;
            mystack.push(str[i]);
        }
    }

    for (int i=0; i<strlen(str); i++)
    {
        if (str[i] == ')')
        {
            cout << "poping " << str[i] << endl;
            mystack.pop();
        }
    }
    
    if(mystack.isEmpty())
        cout << "balanced paranthesis" << endl;
    else
        cout << "not balanced paranthesis" << endl;

}
