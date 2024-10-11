#!/bin/sh

set -e

echo '[{"directory":"'"$(pwd)"'","arguments":["clang","-Iinclude","-x","c","-std=c99","-pedantic","-c","file.c","-o","file.o"],"file":"file.c" }]' > compile_commands.json
