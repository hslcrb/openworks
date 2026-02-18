import argparse
from pathlib import Path
from .file_manager import FileManager
from .planner import Planner
from .subagent_pool import SubagentPool
from .docgen import DocGen

def demo(out: str):
    fm = FileManager()
    fm.make_dir(out)
    # simple demo plan
    request = "Create project summary.\nProduce spreadsheet of top 3 competitors.\nCreate a presentation slide."
    tasks = Planner.plan(request)
    pool = SubagentPool(max_workers=3)

    def worker(task):
        tid = task['id']
        title = task['title']
        detail = task['detail']
        if 'spreadsheet' in detail.lower():
            path = Path(out) / f"competitors_{tid}.xlsx"
            DocGen.create_xlsx(path, 'Competitors', [['name','price'], ['A',100], ['B',120]])
            return {'task': tid, 'file': str(path)}
        if 'presentation' in detail.lower() or 'slide' in detail.lower():
            path = Path(out) / f"deck_{tid}.pptx"
            DocGen.create_pptx(path, title, ['Point A','Point B'])
            return {'task': tid, 'file': str(path)}
        # fallback: create a docx
        path = Path(out) / f"summary_{tid}.docx"
        DocGen.create_docx(path, title, [detail])
        return {'task': tid, 'file': str(path)}

    results = pool.run_parallel(tasks, worker)
    print('Demo results:')
    for r in results:
        print(r)

def main():
    p = argparse.ArgumentParser()
    p.add_argument('cmd', choices=['demo'])
    p.add_argument('--out', default='out')
    args = p.parse_args()
    if args.cmd == 'demo':
        demo(args.out)

if __name__ == '__main__':
    main()
