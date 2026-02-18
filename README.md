Agent Prototype — Local control + multi-step workflows

Overview

This repository contains a minimal Python prototype for an on-device agent that can:

- Access and modify local files and folders.
- Break user requests into multi-step plans and run subtasks.
- Run independent subtasks in parallel (subagents).
- Generate office documents: DOCX, XLSX, PPTX and merge PDFs.
- Provide safety checks and require explicit approvals before destructive actions.

This is a lightweight prototype intended as the foundation for a later Electron app.

Quick start

1. Create and activate a virtualenv:

```bash
python3 -m venv .venv
source .venv/bin/activate
```

2. Install dependencies:

```bash
pip install -r requirements.txt
```

3. Run the demo (creates outputs in `out/`):

```bash
python -m agent.main demo --out out
```

Interactive CLI

You can use the interactive CLI which requests approvals before running plans:

```bash
python -m agent.cli --request "Create summary.\nMake spreadsheet of competitors." --out out
```

For automated demos (skip approvals):

```bash
python -m agent.cli --request "Make slide." --out out --auto-approve
```

Files of interest

- [agent/main.py](agent/main.py)
- [agent/file_manager.py](agent/file_manager.py)
- [agent/planner.py](agent/planner.py)
- [agent/subagent_pool.py](agent/subagent_pool.py)
- [agent/docgen.py](agent/docgen.py)
- [examples/demo.py](examples/demo.py)

Notes

- Playwright or other browser automation is optional and not installed by default here. See `requirements.txt`.
- This prototype isolates code execution in subprocesses and requires explicit user confirmation for destructive operations.

Next steps

If this looks good I can:
- Add a small Electron wrapper shell project.
- Add connectors (Slack, Gmail, Google Drive) scaffolds.
- Integrate Playwright flows for web scraping.