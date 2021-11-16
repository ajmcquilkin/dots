
#! /bin/bash
# https://github.com/johnsci911/eww.widgets/blob/master/launch_eww

## Files and cmd
CONFIG_DIR="$HOME/.eww/bar"
FILE="$HOME/.cache/eww_launch.xyz"
EWW="$HOME/GitHub/eww/target/release/eww -c $CONFIG_DIR"

## Run eww daemon if not running already
if [[ ! `pidof eww` ]]; then
    ${EWW} daemon
    sleep 1
fi

## Open widgets
run_eww() {
    ${EWW} reload
    ${EWW} open-many \
        bar
        # leftBar \
        # centerBar \
        # rightBar
}

## Launch or close widgets accordingly
if [[ ! -f "$FILE" ]]; then
    touch "$FILE"
    run_eww
else
    ${EWW} close-all
    rm "$FILE"
fi
