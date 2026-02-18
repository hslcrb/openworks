#include "Planner.hpp"
#include <iostream>

Planner::Planner(LLMClient* llm) : llm_(llm) {}

void Planner::createPlan(const std::string& request) {
    std::cout << "Creating plan for: " << request << std::endl;
    // For now, static planning (placeholder for LLM-based planning)
    tasks_.push_back({"Identify files to organize", false});
    tasks_.push_back({"Create target folders", false});
    tasks_.push_back({"Move files to folders", false});
}

void Planner::executePlan() {
    for (auto& task : tasks_) {
        std::cout << "Executing: " << task.description << "..." << std::endl;
        // In real use, this would involve tool calls or LLM reasoning
        task.completed = true;
    }
    std::cout << "Plan completed successfully." << std::endl;
}
