//g++ -std=c++14 tests.cpp -o tests && ./tests

#include "../../LinkedList.h"
#include <assert.h> 

#include <array>


void BestCase(){
    //1. allocate a huge memory (8+8)*10000
    int per_node_size = 16;
    int payload_size = 8;
    int node_num = 1000;
    void *location = std::malloc(per_node_size*node_num);
    if (!location) {
        throw std::bad_alloc();
    }
    std::array<double, 1000000> payload_arry = {};
    for (int i = 0; i < node_num; ++i) {
        payload_arry.at(i)=i;
    }

    LinkedList<double *> list;
    for (int i = 0; i < node_num; ++i) {
        char *loc = reinterpret_cast<char *>(location) + i*per_node_size;
        void *node_i = reinterpret_cast<void *>(loc);
        double *payload_i_location = &payload_arry[i];
        list.addNode(node_i, payload_i_location);

//        double *payload_i_location = &payload_arry[i];
//        list.add(i, payload_i_location);
    }

    int index_node_idx = 20000;
    stopwatch_t sw;
    sw.clear();
    sw.start();
//    for (int i = 0; i < index_node_idx; ++i) {
//
//        double t  = *list.get(i);
//        //std::cout<< "list " << i << ":" << t << std::endl;
//
//    }
    double t  = *list.get(index_node_idx);
    auto elapsed = sw.elapsed<std::chrono::milliseconds>();
    std::cout << "linkedlist traversal node"<< index_node_idx <<" in " << elapsed*1000 << " microsecond" << std::endl;
    //std::cout << "linkedlist traversal per node in " << (elapsed*1000)/index_node_idx << " microsecond" << std::endl;
}

void WorstCase(){

    //1. allocate a huge memory (8+8)*10000
    int per_node_size = 16;
    int payload_size = 4*1024; // 64 128 512 1024 2*1024
    int node_num = 256*1024; //4*1024 8*1024 16*1024 32*1024 64*1024
    void *location = std::malloc(per_node_size*node_num+(4*1024)*node_num);
    if (!location) {
        throw std::bad_alloc();
    }
    std::array<Item *, 256*1024> payload_arry = {};
    void *location2 = std::malloc(payload_size*node_num+(4*1024)*node_num);
    for (int i = 0; i < node_num; ++i) {
        char *loc_cpy = reinterpret_cast<char *>(location2) + i*4*1024;
        Item *itm = new Item();

        memset(itm, 'z', payload_size);
        memcpy(loc_cpy, itm, payload_size);
        Item *payload_ = reinterpret_cast<Item *>(loc_cpy);
        payload_arry.at(i)=payload_;
    }

    LinkedList<Item *> list = LinkedList<Item *>();
    for (int i = 0; i < node_num; ++i) {
        char *loc = reinterpret_cast<char *>(location) + i*4*1024;
        void *node_i = reinterpret_cast<void *>(loc);
        Item *payload_i_location = payload_arry[i];
        list.addNode(node_i, payload_i_location);

    }

    int index_node_idx = (node_num-1);
    stopwatch_t sw;
    sw.clear();
    sw.start();

    std::cout << "linkedlist size " << list.size() << std::endl;
    list.printList(index_node_idx);

    auto elapsed = sw.elapsed<std::chrono::milliseconds>();
    std::cout << "linkedlist traversal node index "<< index_node_idx << " in " << elapsed*1000 << " microsecond" << std::endl;
    std::cout << "linkedlist traversal per node in " << (elapsed*1000)/node_num << " microsecond" << std::endl;
}

void TestInlinedPayload(){
    LinkedList<int> list = LinkedList<int>();
    for (int i = 0; i < 10000; ++i) {
        list.add(i);
    }

    for (int i = 0; i < 10000; ++i) {
        std::cout << "linkedlist idx: " <<  list.get(i) << std::endl;
    }
}

int main()
{

    //BestCase();

    WorstCase();


}
