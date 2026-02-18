import re
from typing import List, Optional

def build_mcq_prompt(question: str, choices: List[str]) -> str:
    """Build a prompt instructing the LLM to pick exactly one choice.

    This template favors deterministic responses (numeric index or exact
    choice text). The calling code should validate/parse the reply.
    """
    instr = "다음 보기 중 정확히 하나를 선택하고, 숫자 또는 보기를 응답으로만 보내세요."
    body = question.strip() + "\n\n"
    for i, c in enumerate(choices, start=1):
        body += f"{i}. {c}\n"
    return instr + "\n\n" + body


def parse_mcq_response(resp: str, choices: List[str]) -> Optional[int]:
    """Try to parse an LLM response to a MCQ prompt.

    Returns the 1-based index of the chosen option or None if not clear.
    """
    s = (resp or "").strip()
    if not s:
        return None
    m = re.search(r"\b(\d{1,2})\b", s)
    if m:
        idx = int(m.group(1))
        if 1 <= idx <= len(choices):
            return idx
    # fallback: match by substring against choices
    low = s.lower()
    for i, c in enumerate(choices, start=1):
        if c.lower() in low:
            return i
    return None
