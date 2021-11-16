#! /bin/bash

killall -q "polybar"

for m in $(polybar --list-monitors | cut -d":" -f1); do
	MONITOR=$m polybar --reload -c ~/.config/polybar/config default &
done