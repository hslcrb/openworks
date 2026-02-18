from typing import List, Dict, Any

class Planner:
    """Simple planner: breaks a textual request into numbered subtasks.

    This is a placeholder for a real LLM-driven planner. It returns
    deterministic, objective-style steps where appropriate.
    """

    @staticmethod
    def plan(request: str) -> List[Dict[str, Any]]:
        # Very small heuristic: split on newlines or by sentences.
        parts = [p.strip() for p in request.split('\n') if p.strip()]
        if len(parts) == 0:
            parts = [s.strip() for s in request.split('.') if s.strip()]
        tasks = []
        for i, p in enumerate(parts, start=1):
            tasks.append({
                "id": i,
                "title": p[:80],
                "detail": p,
            })
        return tasks
