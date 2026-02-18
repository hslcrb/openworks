#ifndef PLANNER_HPP
#define PLANNER_HPP

#include <string>
#include <vector>
#include "LLMClient.hpp"

/**
 * Planner Class
 * Breaks down user requests and executes subtasks.
 */
class Planner {
public:
    struct Task {
        std::string description;
        bool completed;
    };

    Planner(LLMClient* llm);
    void createPlan(const std::string& request);
    void executePlan();

private:
    LLMClient* llm_;
    std::vector<Task> tasks_;
};

#endif // PLANNER_HPP
