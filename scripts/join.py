#!/usr/bin/env python3

import json
import sys

from pathlib import Path

build_dir = Path(__file__).parent.joinpath("../build")

commands = []

for project in sys.argv[1:]:
    with open(build_dir.joinpath(project, "compile_commands.json"), encoding="utf-8") as f:
        commands.extend(json.load(f))

print(json.dumps(commands, indent=2))
