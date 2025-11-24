#!/usr/bin/env python3

import json
import sys

from itertools import chain
from pathlib import Path

build_dir = Path(__file__).parent.joinpath("../build").resolve()

commands = []

for project in sys.argv[1:]:
    with open(build_dir.joinpath(project, "compile_commands.json"), encoding="utf-8") as f:
        commands.extend(json.load(f))

for cmd in commands:
    file_path = Path(cmd["file"])
    if file_path.is_relative_to(build_dir):
        file_name = file_path.name.replace(".ino.cpp", ".ino")
        path_segments = filter(lambda s: s not in ("build", "sketch"), file_path.parts[:-1])
        path_segments = chain(path_segments, [file_name])
        cmd["file"] = str(Path(*path_segments))

print(json.dumps(commands, indent=2))
