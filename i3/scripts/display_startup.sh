#! /bin/bash

# ---- Setup scripts ---- #

killall -q "polybar"

~/.config/i3/scripts/monitor_setup.sh
~/.config/i3/scripts/background/set_background.sh
~/.config/polybar/scripts/launch_polybar.sh

