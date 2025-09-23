#include "hash.h"
#include <vector>

// constructor
hashTable::hashTable(int size)
{
    data = std::vector<hashItem>(getPrime(size), hashItem());
    capacity = getPrime(size);
    filled = 0;
} 

int hashTable::insert(const std::string &key, void *pv)
{
    // check if key is already in hashTable
    if (contains(key))
    {
        return 1;
    }
   
    int hash_value = hash(key);
    // first position to try
    while (data[hash_value].isOccupied)
    {
        // if occupied try next one, until you find an empty slot
        hash_value = (hash_value + 1) % capacity;
    }
    data[hash_value].key = key;
    data[hash_value].isOccupied = true;
    // If pv was not provided, the pointer in the hashTable remains nullptr because of the default value
    data[hash_value].pv = pv;
    filled += 1;

    // To keep load factor below 1/2
    if (filled > capacity / 2)
    {
        if (!rehash())
        {
            return 2;
        }
    }
    return 0;
    //double check this one
}

bool hashTable::contains(const std::string &key)
{
    return findPos(key) != -1;
}

void * hashTable::getPointer(const std::string &key, bool *b)
{
    int position = findPos(key);
    if (position == -1)
    {
        if (b != nullptr)
        {
            *b = false;
        }
        return nullptr;
    }
    if (b != nullptr)
    {
        *b = true;
    }
    return data[position].pv;
}

int hashTable::setPointer(const std::string &key, void *pv)
{
    int position = findPos(key);
    if (position == -1)
    {
        return 1;
    }
    data[position].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key)
{
    // find the key
    int position = findPos(key);
    if (position == -1)
    {
        return false;
    }
    // flag the item as deleted
    data[position].isDeleted = true;
    return true;
}

int hashTable::hash(const std::string &key)
{
    unsigned int result = 0;
    for (char character : key)
    {
        result = ((result << 5) + result + character) % capacity; // just multiplying by 33 and adding the character 
    }
    return result;
}

int hashTable::findPos(const std::string &key)
{
    int position = hash(key);
    while (data[position].isOccupied)
    {
        //go until empty or there is a match (with a not-deleted item)
        if (data[position].key == key && (!data[position].isDeleted))
        {
            // this case, we found the key and can return the position
            return position;
        }
        position = (position + 1) % capacity;
    }
    return -1;
}

bool hashTable::rehash()
{
    try
    {
        int new_filled = 0;
        // move the data to a copy
        std::vector<hashItem> copy_data = data;
        int newsize = getPrime(capacity * 2);
        // now data vector is twice as big
        data = std::vector<hashItem>(newsize, hashItem());
        capacity = newsize;

        for (hashItem old_data : copy_data)
        {
            if (!old_data.isDeleted && old_data.isOccupied)
            {
                // insert only the old keys
                insert(old_data.key, old_data.pv);
                new_filled++;
            }
        }

        filled = new_filled;
    }
    // catch block basically sees if anything goes wrong with the allocation, like if memory runs out or something
    catch(const std::bad_alloc &e)
    {
        return false;
    }
    return true;
}

unsigned int hashTable::getPrime(int size)
{
    // if size is bigger than the biggest prime, i should probably throw a bad_alloc exception for later projects
    unsigned int primearray[] = {12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};
    int index = 0;
    while (size >= primearray[index])
    {
        index++;
    }
    return primearray[index];
}
