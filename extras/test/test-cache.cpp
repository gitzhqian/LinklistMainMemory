//g++ -std=c++14 tests.cpp -o tests && ./tests

#include "../../LinkedList.h"
#include <assert.h>

#include <list>
#include <array>
#include <vector>
#include <algorithm>


void FlushCache(){
    //1. allocate two huge memory 4GB+4GB
    int cache_size = 64; //one node size
    int item_size = 64;
    int64_t node_num =  4L*1024*1024*1024/64;
    int64_t data_size =  cache_size * node_num;
    char *node_1 = new char[data_size];
    memset(node_1,'b',data_size);

    char *node_2 = new char[data_size];
    memset(node_2,'v',data_size);


    //2. initialize the traversal array
    std::vector<ItemItem *> items_pointers;
    for (int64_t i = 0; i < node_num; ++i) {
        //void *location = std::malloc(1024*1024*1024);
        char *itm_loc = node_1 + i*cache_size;
        ItemItem *item = reinterpret_cast<ItemItem *>(itm_loc);
        items_pointers.emplace_back(item);
    }

    //3. add them to access list, making the list traversal is random
    LinkedList<ItemItem *> items_list;
    std::random_shuffle(items_pointers.begin(), items_pointers.end());
    for (int64_t i = 0; i < items_pointers.size(); ++i) {
        items_list.add(items_pointers[i]);
//        items_list.emplace_back(items_pointers[i]);
    }

    //4. to flush the cache storage
    for (int64_t n = 0; n < node_num; ++n) {
        char r2 ;
        r2 = *reinterpret_cast<char *>(node_2+n);
        // std::cout << "char  "<< r2 << std::endl;
    }
    std::vector<int64_t> access_loc_random;
    for (int i = 0; i < node_num; ++i) {
        access_loc_random.emplace_back(i);
    }
    std::random_shuffle(access_loc_random.begin(), access_loc_random.end());

    stopwatch_t sw;
    sw.clear();
    sw.start();
    for (int64_t j = 0; j < node_num; ++j) {
        ItemItem *itm = items_list.get(access_loc_random[j]);
        for (int j = 0; j < item_size; ++j) {
            char r ;
            r = itm->itm[j];
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
