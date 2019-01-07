#include<list>
#include <cassert>
#include <iostream>
using namespace std;


template <typename T>
struct Node
    {
        Node<T>* next;
        T data;
    };

template<typename T>
class Deque
{
private:


    Node<T>* first;
    Node<T>* last;


    void copyDeque(Deque<T> const& other)
    {
        Node<T>* temp=other.first;
        //crashes here for no apparent reason
       while(temp!=nullptr){
                this->pushBack(temp->data);
            temp=temp->next;
        }
    }

    void del()
    {
        Node<T>* temp=first;
        while(first!=nullptr)
        {   temp=first;
            first=first->next;
            delete temp;
        }
        last=nullptr;
    }


public:
    Deque():first(nullptr),last(nullptr) {}
    Deque(Deque<T> const& other) :first(nullptr),last(nullptr)
    {   copyDeque(other);
    }
    Deque& operator= (Deque const& other)
    {
        if(this!=&other)
        {
            del();
            copyDeque(other);
        }
        return *this;
    }
    ~Deque()
    {
        del();
    }

    bool isEmpty()const
    {
        return first==nullptr;
    }
    void pushBack(T const& elem)
    {;
        if(isEmpty())
        {
            first=new Node<T>; first->next=nullptr; first->data=elem;
        last=first;
        }
        else{
             last->next=new Node<T>;
            last=last->next;
last->data=elem;
 last->next=nullptr;
        }
    }
    void pushFront(T const& elem)
    {
        if(isEmpty()){first=last=new Node<T>; first->data=elem; first->next=nullptr;}
        else
        {
            Node<T>* newN=new Node<T>;
            newN->data=elem; newN->next=first;
            first=newN;
        }
    }
    T getFront()
    {
        assert(!isEmpty());
        return first->data;
    }
    T getBack()
    {
        assert(!isEmpty());
        return last->data;
    }
    void popBack()
    {   assert(!isEmpty());
        if(first==last){delete first; first=last=nullptr; return;}
        Node<T>* temp=first;
        while(temp->next!=last)temp=temp->next;
        last=temp;
        delete temp->next;
        temp->next=nullptr;

    }
    void popFront()
    {
        assert(!isEmpty());
        Node<T>* toDel=first;
        first=first->next;
        delete toDel;
    }

    size_t size()const
    {
        Node<T>* iter=first;
        if(isEmpty())return 0;
        int count=1;
        while(iter!=last)
        {
            count++;
            iter=iter->next;
        }
        return count;
    }
    friend ostream& operator<<(ostream& out, Deque<T>& mydeque )
    {
        Node<T>* temp=mydeque.first;

        while(temp!=nullptr)
        {
            out<<temp->data<<" ";
            temp=temp->next;
        }
        return out;
    }
    bool operator <(Deque<T>& other)
    {
        return this->size()<other.size();
    }



};
int main()
{
    list <Deque<int>> Mylist;
    Deque<int> mynewDeque;
    mynewDeque.pushBack(3);
    mynewDeque.pushBack(5);
    mynewDeque.pushBack(4);


    Deque<int> mynewDeque1;
    mynewDeque1.pushBack(3);
    mynewDeque1.pushBack(5);


    Deque<int> mynewDeque2;
    mynewDeque2.pushBack(3);

 Mylist.push_back(mynewDeque1);
 Mylist.push_back(mynewDeque2);
 Mylist.push_back(mynewDeque);
 //pushing 3 deacks



   Mylist.sort();

 //adding at the proper spot

    auto it=Mylist.begin();
    while((*it)<mynewDeque && it!=Mylist.end())
    {
        ++it;
    }
    Mylist.insert(it,mynewDeque1);
//simple print

    for(auto it=Mylist.begin();it!=Mylist.end();it++)
    {
        cout<<*it<<endl;
    }




    //bonus task :
    list<int> newList;
    for(auto it=Mylist.begin();it!=Mylist.end();it++)
    {
        int front=(*it).getFront();
        int back=(*it).getBack();
        if(front<(front+back)/2) newList.push_back(front);
        else newList.push_back(back);

    }

    //print of new list
    for(auto it=newList.begin();it!=newList.end();it++)
cout<<*it<<endl;



    return 0;
}
