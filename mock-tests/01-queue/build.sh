#!/usr/bin/env bash
# Build every .cpp file in this folder into ./test.out and run the tests.
# AddressSanitizer is on, so shallow copies / double frees / out-of-bounds
# writes crash loudly instead of "working by accident".
# Usage: ./build.sh            build and run
#        ./build.sh --no-run   only build

set -euo pipefail

cd "$(dirname "$0")"

compiler="${CXX:-g++}"
"$compiler" -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-private-field -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  *.cpp -o test.out

echo "Built ./test.out"

if [[ "${1:-}" != "--no-run" ]]; then
  ./test.out
fi
