#ifndef SAFETY_APPROVER_HPP
#define SAFETY_APPROVER_HPP

#include <string>

/**
 * SafetyApprover Class
 * Manages user approvals for destructive or critical actions.
 */
class SafetyApprover {
public:
    enum class Permission {
        ALLOW,
        BLOCK,
        ASK
    };

    static bool requestApproval(const std::string& action);
    static Permission getPolicy(const std::string& action);
};

#endif // SAFETY_APPROVER_HPP
