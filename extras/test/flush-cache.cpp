//g++ -std=c++14 tests.cpp -o tests && ./tests

#include "../../LinkedList.h"
#include <assert.h>


#include <array>
#include <vector>
#include <algorithm>

void CacheTest(){
    //1. allocate a huge memory (8+8)*10000
    int cache_size = 1024*1024*1024; //one node size
    int item_size = 56;
    int node_num =  20;
    size_t size =  1024 * 1024 * 1024;

    std::array<char, 20*1000*1000*64> result = {};

    LinkedList<Item> list;
    std::vector<int> access;
    for (int i = 0; i < node_num; ++i) {
        char *node_i = new char[size];
        memset(node_i,'c',size);
        Item *node_i_data = reinterpret_cast<Item *>(node_i);
        list.addNode(reinterpret_cast<void *>(node_i), *node_i_data);
        //list.add(node_i);
        access.emplace_back(i);
    }
    std::random_shuffle(access.begin(), access.end());

    stopwatch_t sw;
    sw.clear();
    sw.start();
    for (int i = 0; i < access.size(); ++i) {
        auto itm = list.get(access[i]);
        for (int j = 0; j < item_size; ++j) {
            char r = itm.itm[j];
            result[i*j] = r;
            //std::cout << "char  "<< r << std::endl;
        }
    }

    auto elapsed = sw.elapsed<std::chrono::nanoseconds>();
    std::cout << "linkedlist traversal "<< node_num <<" node average in " << elapsed/node_num  << " nanoseconds" << std::endl;

}


int main()
{

    FlushCache();

}
