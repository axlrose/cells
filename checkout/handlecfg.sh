#!/bin/bash
configfile="$1"
sed 's/buildmode=user\( *\)once/buildmode=eng/' "$configfile"
sed 's/buildmode=eng\( *\)once/buildmode=user/' "$configfile"

sed 's/switch=on\( *\)once/switch=off/' "$configfile"
sed 's/switch=off\( *\)once/switch=on/' "$configfile"
