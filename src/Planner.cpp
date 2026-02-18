#include "Planner.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Planner::Planner(LLMClient* llm) : llm_(llm) {}

void Planner::createPlan(const std::string& request) {
    std::cout << "Creating dynamic plan for: " << request << std::endl;
    
    std::string prompt = "Break down the following user request into a JSON list of subtasks. Each task should have a 'description' field.\nRequest: " + request;
    prompt += "\nRespond ONLY with a JSON array of objects, e.g., [{\"description\": \"...\"}]";
    
    LLMClient::Response resp = llm_->chat(prompt);
    if (!resp.success) {
        std::cerr << "Planning failed. Using fallback." << std::endl;
        tasks_.push_back({"Analyze request manually", false});
        return;
    }

    try {
        json planJson = json::parse(resp.text);
        for (auto& item : planJson) {
            tasks_.push_back({item["description"].get<std::string>(), false});
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing plan JSON: " << e.what() << std::endl;
        tasks_.push_back({"Identify tasks for: " + request, false});
    }
}

#include "FileManager.hpp"
#include "DocGenerator.hpp"
#include "ThreadPool.hpp"
#include "SafetyApprover.hpp"

void Planner::executePlan() {
    ThreadPool pool(4); // 4 threads for subagents
    std::vector<std::future<void>> results;

    for (auto& task : tasks_) {
        results.emplace_back(pool.enqueue([this, &task] {
            std::cout << "[Subagent] Analyzing request: " << task.description << "..." << std::endl;
            
            // Safety check
            if (SafetyApprover::getPolicy(task.description) == SafetyApprover::Permission::ASK) {
                if (!SafetyApprover::requestApproval(task.description)) {
                    std::cout << "[Subagent] Task blocked by user: " << task.description << std::endl;
                    return;
                }
            }

            // Logic to decide tool based on description
            if (task.description.find("folder") != std::string::npos || task.description.find("file") != std::string::npos) {
                std::cout << "[Subagent] Using FileManager for: " << task.description << std::endl;
            } else if (task.description.find("document") != std::string::npos || task.description.find("docx") != std::string::npos) {
                DocGenerator::generateDocx("output.docx", "Task Result", task.description);
            }

            task.completed = true;
            std::cout << "[Subagent] Finished: " << task.description << std::endl;
        }));
    }

    // Wait for all subtasks
    for (auto& res : results) res.get();
    
    std::cout << "Plan execution completed successfully." << std::endl;
}
