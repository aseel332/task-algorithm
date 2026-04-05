#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>

class Worker{
  public: 
    int _id;
    float _price;
    bool _occupied;
    int _finish;

    Worker(int id, float price, bool occupied, int finish);
};

#endif