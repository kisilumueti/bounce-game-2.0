#!/usr/bin/env python3
"""Validate a Neon Bounce score-export JSON file without modifying it."""
import argparse
import json
from pathlib import Path
from collections import Counter

def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("file", type=Path, help="Path to exported score JSON")
    args = parser.parse_args()
    try:
        payload = json.loads(args.file.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        parser.error(f"cannot read valid JSON: {exc}")
    profile = payload.get("profile")
    if not isinstance(profile, dict):
        parser.error("missing profile object")
    history = profile.get("history", [])
    if not isinstance(history, list):
        parser.error("profile.history must be an array")
    valid, invalid = [], 0
    for row in history:
        if not isinstance(row, dict) or isinstance(row.get("score"), bool):
            invalid += 1
            continue
        try:
            score = int(row["score"])
        except (KeyError, TypeError, ValueError):
            invalid += 1
            continue
        if score < 0:
            invalid += 1
            continue
        valid.append((str(row.get("name", "PLAYER"))[:18], score))
    print("NEON BOUNCE SCORE AUDIT")
    print(f"Records checked : {len(history)}")
    print(f"Valid records   : {len(valid)}")
    print(f"Invalid records : {invalid}")
    print(f"Best score      : {max((score for _, score in valid), default=0)}")
    print(f"Unique names    : {len(Counter(name for name, _ in valid))}")
    for index, (name, score) in enumerate(sorted(valid, key=lambda item: item[1], reverse=True)[:10], 1):
        print(f"{index:02d}. {name:<18} {score:>10,}")
    return 0 if not invalid else 2

if __name__ == "__main__":
    raise SystemExit(main())