"""Check that the handoff documents point at things that exist (RG-GDK-025).

README.md, AGENTS.md, CONTRIBUTING.md, docs/**/*.md and research/**/*.md are what an agent or
developer follows with no other context. Every relative Markdown link and every
backticked repository path in them must resolve. The exact issue bodies under
docs/roadmap are checked by validate_roadmap.py instead.

    python scripts/check_docs.py        # exit 1 and list problems if any
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# Backticked text starting with one of these is a repository path.
PATH_ROOTS = ('src/', 'include/', 'tests/', 'scripts/', 'docs/', 'cmake/', 'resources/',
              'tools/', 'thirdparty/', '.github/', 'research/')
LINK = re.compile(r'\[[^\]]*\]\(([^)\s]+)\)')
CODE = re.compile(r'`([^`\n]+)`')


def documents(root):
    yield from (root / name for name in ('README.md', 'AGENTS.md', 'CONTRIBUTING.md')
                if (root / name).is_file())
    for path in sorted((root / 'docs').rglob('*.md')):
        if 'roadmap' not in path.relative_to(root).parts[1:2]:
            yield path
    yield from sorted((root / 'research').rglob('*.md'))


def is_checkable_path(text):
    # src/xenia/... names files in the upstream Xenia/Canary/Edge trees.
    if not text.startswith(PATH_ROOTS) or text.startswith('src/xenia/'):
        return False
    # Placeholders, globs, alternatives, commands and ranges are not literal paths.
    return not re.search(r'[<>*{}|$ ,\[\]]|\.\.\.|…', text)


def problems_in(path, root):
    found = []
    text = path.read_text(encoding='utf-8')
    for line_number, line in enumerate(text.splitlines(), 1):
        for target in LINK.findall(line):
            if re.match(r'[a-z]+:', target) or target.startswith('#'):
                continue
            file_part = target.split('#', 1)[0]
            if file_part and not (path.parent / file_part).exists():
                found.append(f'{path.relative_to(root)}:{line_number}: broken link {target}')
        for code in CODE.findall(line):
            candidate = code.strip().rstrip('.,:;)')
            candidate = re.sub(r':\d+(-\d+)?$', '', candidate)  # file:line references
            if is_checkable_path(candidate) and not (root / candidate).exists():
                found.append(f'{path.relative_to(root)}:{line_number}: missing path {candidate}')
    return found


def check(root=ROOT):
    problems = []
    for path in documents(root):
        problems.extend(problems_in(path, root))
    return problems


def main():
    problems = check()
    for problem in problems:
        print(problem)
    print(f'{len(problems)} problem(s) in handoff documents')
    return 1 if problems else 0


if __name__ == '__main__':
    raise SystemExit(main())
