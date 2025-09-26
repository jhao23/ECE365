#include <vector>
#include <string>

#include "../program1/hash.h"
#include <string>

class heap()
{
    public:
        
        heap(int capacity);

        int insert(const std::string &id, int key, void *pv = nullptr);

        int setKey(const std::string &id, int key);

        int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

        int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

    private:

        class Node()
        {
            std::string id;
            int key;
            void *pData;
        }

        int size;
        int capacity;
        std::vector<Node> data;
        hashTable idHash;

        void percolateUp(int posCur);
        void percolateDown(int posCur);
        int getPos(node *pn);
}
