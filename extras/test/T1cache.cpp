//g++ -std=c++14 tests.cpp -o tests && ./tests

#include "../../LinkedList.h"
#include <assert.h>


#include <array>
#include <vector>
#include <algorithm>

void T1CacheTest(){
    //1. allocate a huge memory 20 GB
    int64_t item_size = 56;
    int64_t node_num =  10;
    int64_t chunk_size = 1024*1024*1024;
    int64_t data_size =  1024 * 1024 * 1024 * node_num;
    char *chunk_1 = new char[data_size];
    memset(chunk_1,'b',data_size);

    // allocate a huge memory 2 GB
    int64_t flush_size = 2*chunk_size;
    char *chunk_2 = new char[flush_size];
    memset(chunk_2,'v',flush_size);

    // 2. create list, each node occupy the first 64 bytes of the chunk
    LinkedList<Item> list;
    std::vector<int64_t> access_loc_random;
    for (int64_t i = 0; i < node_num; ++i) {
        char *itm_loc = chunk_1 + i*chunk_size; //node location
        Item *itm_data = reinterpret_cast<Item *>(itm_loc); //item
        list.addNode(reinterpret_cast<void *>(itm_loc), *itm_data);
        access_loc_random.emplace_back(i);
    }
    std::random_shuffle(access_loc_random.begin(), access_loc_random.end());

    //3. to flush the cache storage
    for (int64_t n = 0; n < node_num; ++n) {
        char r2 ;
        r2 = *reinterpret_cast<char *>(chunk_2+n);
        // std::cout << "char  "<< r2 << std::endl;
    }

    //4. start test
    stopwatch_t sw;
    sw.clear();
    sw.start();
    for (int64_t i = 0; i < access_loc_random.size(); ++i) {
        auto itm = list.get(access_loc_random[i]);
        for (int64_t j = 0; j < item_size; ++j) {
            char r ;
            r = itm.itm[j];
            //std::cout << "char  "<< r << std::endl;
        }
    }

    auto elapsed = sw.elapsed<std::chrono::nanoseconds>();
    std::cout << "linkedlist traversal "<< node_num <<" node average in " << elapsed/node_num  << " nanoseconds" << std::endl;

}


int main()
{

    T1CacheTest();

}
