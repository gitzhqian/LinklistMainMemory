//g++ -std=c++14 tests.cpp -o tests && ./tests

#include "../../LinkedList.h"
#include <assert.h>


#include <array>
#include <vector>
#include <algorithm>
#include <random>

void TBandCache(){
    //1. allocate two huge memory 8GB+8GB
    int64_t cache_size = 64; //one node size
    int64_t item_size = 64;
    int64_t node_num =  1L*1024*1024*1024/64;
    int64_t data_size =  cache_size * node_num;
    char *node_1 = new char[data_size];
    memset(node_1,'b',data_size);

    char *node_2 = new char[data_size];
    memset(node_2,'v',data_size);

    //2. initialize the access array
    std::vector<ItemItem *> items_pointers;
    for (int64_t i = 0; i < node_num; ++i) {
        char *itm_loc = node_1 + i*cache_size;
        ItemItem *item = reinterpret_cast<ItemItem *>(itm_loc);
        items_pointers.emplace_back(item);
    }

    //shuffle
     std::random_device rd;
     std::mt19937 g(rd());
     std::shuffle(items_pointers.begin(), items_pointers.end(), g);

    //3. to flush the cache storage
    for (int64_t n = 0; n < node_num; ++n) {
        char r2 ;
        r2 = *reinterpret_cast<char *>(node_2+n);
        // std::cout << "char  "<< r2 << std::endl;
    }

    //4. start test, sequential read
    stopwatch_t sw;
    sw.clear();
    sw.start();
    for (int64_t i = 0; i < node_num ; ++i) {
        ItemItem *itm;
        itm = items_pointers.at(i);
        for (int j = 0; j < item_size; ++j) {
            char r;
            r = itm->itm[j];
            //std::cout << "char  "<< r << std::endl;
        }
    }

    auto elapsed = sw.elapsed<std::chrono::nanoseconds>();
    std::cout << "linkedlist traversal "<< node_num <<" node average in " << elapsed/node_num  << " nanoseconds" << std::endl;

}


int main()
{

    TBandCache();


}
