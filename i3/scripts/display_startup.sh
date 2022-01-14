#! /bin/bash

# ---- Setup scripts ---- #

killall -q "polybar"

/home/ajmcquilkin/.config/i3/scripts/monitor_setup.sh
/home/ajmcquilkin/.config/i3/scripts/background/set_background.sh
/home/ajmcquilkin/.config/polybar/scripts/launch_polybar.sh

