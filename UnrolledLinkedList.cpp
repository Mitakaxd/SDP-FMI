#include<iostream>
using namespace std;

#define maxElements 10
template <typename T>
struct Node
{
public:
    Node* next;
    int size;
    T arr[maxElements];
    Node(T const* arr_ = nullptr, int size_ = 0, Node* next_ = nullptr)
    {
        if (arr_ != nullptr)for (int i = 0; i < size_; i++)arr[i] = arr_[i];
        size = size_;
        next = next_;
    }
};
template<typename T>
class UnrolledLinkedList
{
private:
    Node<T>* first;

    void copyme(UnrolledLinkedList<T> const& other)
    {
        for(auto it=other.begin(); it!=other.end(); it++)
        {
            this->pushBackAtList((*it));
        }
    }
    void del()
    {
        Node<T>* temp;
        while (first->next != nullptr)
        {
            temp = first;
            first = first->next;
            delete temp;
        }
        delete first;
    };

    class Iterator
    {
    private:
        Node<T>* curNode;
        int IdxinArray;
    public:
        Iterator(Node<T>* curNode_=nullptr,int IdxinArray_=-1):curNode(curNode_),IdxinArray(IdxinArray_) {}
        Iterator(Iterator const& other):Iterator(other.getNode(),other.getIdx()) {}
        Iterator& operator++()
        {
            if(IdxinArray==curNode->size-1)
            {
                curNode=curNode->next;
                IdxinArray=0;
            }
            else IdxinArray++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp=(*this);
            ++(*this);
            return temp;
        }
        T& operator* ()
        {
            return curNode->arr[IdxinArray];
        }
        void operator +(int times)
        {
            for(times; times>=0; times--)
            {
                ++(*this);
            }
        }
        Node<T>* getNode()const
        {
            return curNode;
        }
        int getIdx()const
        {
            return IdxinArray;
        }
        bool operator ==(Iterator const& second)
        {
            if(this->curNode==second.getNode()&& this->IdxinArray==second.getIdx())return true;
            return false;
        }
        bool operator!=(Iterator const& second)
        {
            return !((*this)==second);
        }

    };



public:

    Iterator begin()
    {
        return Iterator(first,0);
    }
    Iterator end()
    {
        Node<T>* temp=first;
        while(temp->next!=nullptr)temp=temp->next;
        return Iterator(temp,temp->size-1);
    }

    UnrolledLinkedList<T>& operator=(UnrolledLinkedList<T> const& other)
    {
        if (this != &other)
        {
            del();
            copy(other);
        }
        return *this;
    }
    UnrolledLinkedList(UnrolledLinkedList<T> const& other)
    {
        this->copyme(other);
    }

    UnrolledLinkedList() :first(nullptr) {}
    ~UnrolledLinkedList()
    {
        del();
    }
    bool empty()const
    {
        return first == nullptr;
    }
    int countElem()const
    {
        int countof = 0;
        Node<T>* temp = first;
        if (temp == nullptr)return 0;
        else
        {
            while (temp->next != nullptr)
            {
                countof += temp->size;
                temp=temp->next;
            }
            countof+=temp->size;//for the last node
        }
        return countof;
    }

    void FindAndDel(T const& elem)
    {
        Node<T>* temp = first;
        while (temp->next != nullptr)
        {
            //deleting the found elements from this node
            for (int i = 0; i < temp->size; i++)
            {
                if (temp->arr[i] == elem)
                {
                    for (int j = i; j < temp->size; j++)
                    {
                        temp->arr[j] = temp->arr[j + 1];
                    }
                    temp->size--;
                }
            }
            //check if we have to move objects
            if (temp->size < maxElements / 2)
            {
                if (temp->next->size - (maxElements / 2 - temp->size) < maxElements / 2) //have to remove the whole next box
                {
                    for (int i = 0; i < temp->next->size; i++)
                    {
                        temp->arr[temp->size] = temp->next->arr[i];
                        temp->size++;
                    }
                    Node<T>* temp2=temp->next;//box to delete
                    temp->next=temp2->next;//pointer skipping a box
                    delete temp2;
                }
                //else just a few elements
                else
                {
                    int transfercount = maxElements / 2 - temp->size;
                    //saving the elements in the first node
                    for (int i = 0; i < transfercount; i++)
                    {
                        temp->arr[temp->size + i] = temp->next->arr[i];
                    }

                    //shift left on the next node

                    for (int i = 0; i < temp->next->size - transfercount; i++)
                    {
                        temp->next->arr[i] = temp->next->arr[i + transfercount];
                    }
                    temp->next->size = temp->next->size - transfercount;
                    temp->size = maxElements / 2;

                }

            }

            //iterating
            temp = temp->next;
        }
    }




    void insertByIdxIdx(int idx1, int idx2, T const& elem)
    {
        Node<T>* temp = first;
        for (int i = 0; i < idx1; i++)
        {
            temp = temp->next;
        }

        if (temp->size == maxElements) //creating new node
        {
            T arr[maxElements / 2];
            int newNodeSize = temp->size - maxElements / 2; //second half of the elements
            for (int i = maxElements / 2; i < temp->size; i++)
            {
                arr[i - maxElements / 2] = temp->arr[i];    //copy the elements in a buffer array
            }
            temp->size = maxElements / 2;
            temp->next = new Node<T>(arr, newNodeSize, temp->next);
        }
        if (idx2 < maxElements / 2) temp->arr[idx2] = elem;//saving elem if j<n
        else temp->next->arr[idx2 - maxElements / 2] = elem;//saving elem if j>n

    }


    void pushBackAtNode(int idx, T const& elem)
    {
        Node<T>* temp = first;

        for (int i = 0; i < idx; i++)
        {
            if (temp == nullptr)throw "OutofBounds";    //finding the node
            temp = temp->next;
        }
        if (temp->size == maxElements) //creating new node
        {
            T arr[maxElements / 2];
            int newNodeSize = temp->size - maxElements / 2; //second half of the elements
            for (int i = maxElements / 2; i < temp->size; i++)
            {
                arr[i - maxElements / 2] = temp->arr[i];    //copy the elements in a buffer array
            }
            temp->size = maxElements / 2;
            temp->next = new Node<T>(arr, newNodeSize, temp->next);

        }
        temp->arr[temp->size++] = elem;//saving new element


    }





    void pushBackAtList(T const& elem)
    {
        if (this->empty())
        {
            first = new Node<T>();
            first->arr[0] = elem;
            first->size++;
        }
        else
        {
            Node<T>* temp = first;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            if (temp->size == maxElements)
            {
                //we have to move to new Node
                T arr[maxElements / 2];
                int newNodeSize = temp->size - maxElements / 2; //second half of the elements
                for (int i = maxElements / 2; i < temp->size; i++)
                {
                    arr[i - maxElements / 2] = temp->arr[i];    //copy the elements in a buffer array
                }
                temp->size = maxElements / 2;

                temp->next = new Node<T>(arr, newNodeSize, nullptr); //create our new node initialized with buffer array
                temp = temp->next;
            }
            temp->arr[temp->size++] = elem;//saving new element
        }
    }

    void AddIter(int idx,T const& elem)
    {
        auto it=begin();
        int countNodes=0;
        Node<T>* previous=it.getNode();
        for(int i=0; i<idx; i++)
        {
            it++;
            if(it.getNode()!=previous)countNodes++;
        }
//to reuse the code for insert by two idxes, we count the nodes and use the it for the rest
        insertByIdxIdx(countNodes,it.getIdx(),elem);
    }
    void RemoveIter(int idx)
    {
        auto it=begin();
        for(int i=0; i<idx; i++)
        {
            it++;
        } //finding elem

        auto it2=it;
        it2++; //using two iterators to left shift everything after from our element forward
        while(it!= end() && it2!=end())
        {

            *it=*it2;
            it++;
            it2++;
        }
        it2.getNode()->size--;
    }

};

int main()
{
    UnrolledLinkedList<int> llist;
    for (int i = 0; i<50; i++)
    {
        llist.pushBackAtList(i);
    }
    int size = llist.countElem();
      int a = 5;
    llist.insertByIdxIdx(4,9,a);

    llist.FindAndDel(a);

    llist.AddIter(3, 5);

    llist.RemoveIter(8);


    return 0;
}
