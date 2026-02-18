from pathlib import Path
from typing import List

class FileManager:
    def __init__(self, base: str | Path = "."):
        self.base = Path(base).resolve()

    def _abs(self, p: str | Path) -> Path:
        p = Path(p)
        if p.is_absolute():
            return p
        return (self.base / p).resolve()

    def read_text(self, path: str | Path) -> str:
        p = self._abs(path)
        return p.read_text(encoding="utf-8")

    def write_text(self, path: str | Path, data: str, overwrite: bool = True) -> Path:
        p = self._abs(path)
        p.parent.mkdir(parents=True, exist_ok=True)
        if p.exists() and not overwrite:
            raise FileExistsError(f"File exists: {p}")
        p.write_text(data, encoding="utf-8")
        return p

    def list_dir(self, path: str | Path = ".") -> List[Path]:
        p = self._abs(path)
        return [x for x in p.iterdir()]

    def make_dir(self, path: str | Path) -> Path:
        p = self._abs(path)
        p.mkdir(parents=True, exist_ok=True)
        return p

    def rename(self, src: str | Path, dst: str | Path, overwrite: bool = False) -> Path:
        s = self._abs(src)
        d = self._abs(dst)
        d.parent.mkdir(parents=True, exist_ok=True)
        if d.exists() and not overwrite:
            raise FileExistsError(f"Destination exists: {d}")
        s.rename(d)
        return d

    def delete(self, path: str | Path) -> bool:
        p = self._abs(path)
        if p.is_dir():
            for child in p.iterdir():
                if child.is_file():
                    child.unlink()
            p.rmdir()
            return True
        if p.exists():
            p.unlink()
            return True
        return False
