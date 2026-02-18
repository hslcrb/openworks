import concurrent.futures
from typing import Callable, Iterable, Any, List, Dict

class SubagentPool:
    def __init__(self, max_workers: int = None):
        self.max_workers = max_workers

    def run_parallel(self, tasks: Iterable[Dict], worker: Callable[[Dict], Any]) -> List[Any]:
        """Run independent subtasks in parallel using threads by default.

        `worker` is a callable that accepts a task dict and returns a result.
        """
        results = []
        with concurrent.futures.ThreadPoolExecutor(max_workers=self.max_workers) as ex:
            futures = [ex.submit(worker, t) for t in tasks]
            for f in concurrent.futures.as_completed(futures):
                try:
                    results.append(f.result())
                except Exception as e:
                    results.append({"error": str(e)})
        return results
