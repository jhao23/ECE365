#include <vector>
#include <string>
#include "heap.h"
// Need to add comments to heap.h file for documentation

heap::heap(int capacity)
{
    size = 0;
    this->capacity = capacity;
    data.resize(capacity + 1);
    idHash = hashTable(capacity * 4);
    //make sure there is enough room in the hashTable
}

int heap::insert(const std::string &id, int key, void *pv)
{
    if (size == capacity)
    {
        return 1;
    }

    if (idHash.contains(id))
    {
        return 2;
    }

    Node newData= Node();
    newData.id = id;
    newData.key = key;
    newData.pData = pv;
  
    // Store the node in both the heap and the hashtable
    data[size + 1] = newData;
    
    Node *point = &data[size + 1];
    idHash.insert(id, point);

    // keep the heap property with the percolateUp
    percolateUp(size + 1);
    size++;
    return 0;
}

int heap::setKey(const std::string &id, int key)
{
    if (!idHash.contains(id))
    {
        return 1;
    }
    
    //have to static_cast into Node* because getPos takes a Node* as an argument
    int position = getPos( static_cast<Node*> (idHash.getPointer(id)) );

    //effectively increaseKey 
    if (data[position].key < key)
    {
        data[position].key = key;
        percolateDown(position);
    }
    //effectively decreaseKey
    else if (data[position].key > key)
    {
        data[position].key = key;
        percolateUp(position);
    }

    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (size == 0)
    {
        return 1;
    }

    if (pId != nullptr)
    {
        *pId = data[1].id;
    }

    //easier to just call remove instead of implementing it again
    remove(data[1].id, pKey, ppData);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    if (!idHash.contains(id))
    {
        return 1;
    }

    int position = getPos( static_cast<Node*> (idHash.getPointer(id)) ); //cast the pointer directly later
    int oldKey = data[position].key;

    if (pKey != nullptr)
    {
        *pKey = data[position].key;
    }
    if (ppData != nullptr)
    {
        *(static_cast<void **>(ppData)) = data[position].pData;
    }

    idHash.remove(data[position].id);
    //lazy deletion and overwriting of node
    data[position] = data[size];
    idHash.setPointer(data[position].id, &data[position]);
    // there are cases where percolate might never be called or percolate doesn't update the hashtable, so we have to update the location here
    size--;
    // decreasing the size here allows the percolate to function properly (node is now outside the consideration of percolate)

    if (oldKey < data[position].key)
    {
        percolateDown(position);
    }
    else if (oldKey > data[position].key)
    {
        percolateUp(position);
    }

    return 0;
}

void heap::percolateUp(int posCur)
{
    while( posCur != 1 && (data[posCur].key < data[posCur / 2].key) )
    {
        Node temp = data[posCur];
        data[posCur] = data[posCur / 2];
        data[posCur / 2] = temp;
        //just swapping nodes until we get to the top or the node is in the correct position

        idHash.setPointer(data[posCur].id, &data[posCur]);
        idHash.setPointer(data[posCur / 2].id, &data[posCur / 2]);
        //sets all of the pointers in the hashmap to the correct spots
        posCur = posCur / 2;
    }
}

void heap::percolateDown(int posCur)
{
    while( posCur * 2 <= size )
    {
        int swapPos = posCur * 2;
        // check whether the right child is less than the left child
        if (2 * posCur + 1 <= size && data[2*posCur].key > data[2*posCur+1].key)
        {
            swapPos = posCur * 2 + 1;
        }

        if (data[posCur].key > data[swapPos].key)
        {
            Node temp = data[posCur];
            data[posCur] = data[swapPos];
            data[swapPos] = temp;
            
            idHash.setPointer(data[posCur].id, &data[posCur]);
            idHash.setPointer(data[swapPos].id, &data[swapPos]);
            //reorganizing the hash table

            posCur = swapPos;
        }
        else
        {
            break;
        }
    }
}

int heap::getPos(Node *pn)
{
    int position = pn - &data[0];
    return position;
}
