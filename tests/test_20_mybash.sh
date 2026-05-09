#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EXERCISE_DIR="$SCRIPT_DIR/../exercises/20_mybash"
EXERCISE_DIR="$(cd "$EXERCISE_DIR" && pwd)"

CMD_FILE=$(mktemp)
trap "rm -f $CMD_FILE" EXIT

cat > "$CMD_FILE" <<EOF
myfile $EXERCISE_DIR/bin/mybash
myfile $EXERCISE_DIR/obj/mybash/main.o
mysed s/unix/linux/ "unix is opensource. unix is free os."
mytrans $EXERCISE_DIR/src/mytrans/text.txt
mywc $EXERCISE_DIR/src/mytrans/text.txt
EOF

cd "$EXERCISE_DIR"
./20_mybash "$CMD_FILE"
