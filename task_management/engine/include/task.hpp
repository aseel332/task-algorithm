#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include<string>

class Task{
  public:
    int task_id;
    int priority;
    int complexity_score;
    std::string preferred;
    std::string status;
    int complete_time;
    float profit;
    Task() {}
    Task(int task, int pri, int cmp, std::string pref, std::string sta, int ct, float rew);
};

#endif