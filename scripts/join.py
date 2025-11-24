#!/usr/bin/env python3

import json
import sys

from pathlib import Path

build_dir = Path(__file__).parent.joinpath("../build")

commands = []

for project in sys.argv[1:]:
    with open(build_dir.joinpath(project, "compile_commands.json"), encoding="utf-8") as f:
        commands.extend(json.load(f))

for cmd in commands:
    cmd["file"] = cmd["file"].replace("/build", "")
    cmd["file"] = cmd["file"].replace("/sketch", "")
    cmd["file"] = cmd["file"].replace(".ino.cpp", ".ino")

print(json.dumps(commands, indent=2))
