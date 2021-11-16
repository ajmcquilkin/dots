#! /bin/bash

# https://askubuntu.com/questions/4507/how-do-i-disable-middle-mouse-button-click-paste
# Disables center scroll to paste
pkill xbindkeys
xbindkeys -p

~/.config/i3/scripts/scroll_direction_startup.sh
~/.config/i3/scripts/display_startup.sh
