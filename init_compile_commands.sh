#!/bin/sh

set -e

cd "$(dirname "$0")"

mkdir -p .cache
echo "int main() { return 0; }" | clang -x c - -o /dev/null -MJ .cache/tmp.json.part
(echo "[" && cat .cache/tmp.json.part && echo "]") > compile_commands.json
