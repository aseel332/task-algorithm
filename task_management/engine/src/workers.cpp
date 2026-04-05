#include "../include/worker.hpp"
#include<iostream>

Worker::Worker(int id, float price, bool occupied, int finish){
  _id = id;
  _price = price;
  _occupied = occupied;
  _finish = finish;
};