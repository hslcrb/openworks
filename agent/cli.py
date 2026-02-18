import argparse
from pathlib import Path
from .file_manager import FileManager
from .planner import Planner
from .subagent_pool import SubagentPool
from .docgen import DocGen
from .approver import Approver


def run_request(request: str, out: str, auto_approve: bool = False, max_workers: int = 3):
    fm = FileManager()
    fm.make_dir(out)
    tasks = Planner.plan(request)
    print(f"Planned {len(tasks)} task(s):")
    for t in tasks:
        print(f"- [{t['id']}] {t['title']}")

    approver = Approver(auto_approve=auto_approve)
    if not approver.request("Approve plan execution", '\n'.join(t['detail'] for t in tasks)):
        print("Plan denied. Exiting.")
        return

    pool = SubagentPool(max_workers=max_workers)

    def worker(task):
        tid = task['id']
        detail = task['detail']
        # simple heuristics for demo
        if 'spreadsheet' in detail.lower() or 'excel' in detail.lower():
            path = Path(out) / f"competitors_{tid}.xlsx"
            DocGen.create_xlsx(path, 'Competitors', [['name', 'price'], ['A', 100], ['B', 120]])
            return {'task': tid, 'file': str(path)}
        if 'presentation' in detail.lower() or 'slide' in detail.lower() or 'ppt' in detail.lower():
            path = Path(out) / f"deck_{tid}.pptx"
            DocGen.create_pptx(path, task['title'], ['Point A', 'Point B'])
            return {'task': tid, 'file': str(path)}
        # default: write docx summary
        path = Path(out) / f"summary_{tid}.docx"
        DocGen.create_docx(path, task['title'], [detail])
        return {'task': tid, 'file': str(path)}

    results = pool.run_parallel(tasks, worker)
    print('Results:')
    for r in results:
        print(r)


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--request', '-r', help='Text request to plan and run')
    p.add_argument('--out', default='out')
    p.add_argument('--auto-approve', action='store_true')
    p.add_argument('--max-workers', type=int, default=3)
    args = p.parse_args()
    if not args.request:
        print('Provide --request with the action to run')
        return
    run_request(args.request, args.out, auto_approve=args.auto_approve, max_workers=args.max_workers)


if __name__ == '__main__':
    main()
