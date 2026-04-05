#include "../include/task.hpp"
#include <iostream>
#include <string>

Task::Task(int task, int pri, int cmp, std::string pref, std::string sta, int ct, float rew){
      task_id = task;
      priority = pri;
      complexity_score = cmp;
      preferred = pref;
      status = sta;
      complete_time = ct;
      profit = rew;
    }