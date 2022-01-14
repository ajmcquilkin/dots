#! /bin/bash

echo $($HOME/.config/eww/lock/scripts/get_todo_list.sh)
# echo $tasks

# IFS=', '
# read -a workspaces <<< "$ws"

# printf "(box :orientation \"h\" :class \"workspaces\" :halign \"start\" :valign \"center\" :spacing 9 "
# for w in "${workspaces[@]}"; do
#   printf "(button :class \"$([ $active_workspace = $w ] && echo 'workspace_active' || echo 'workspace')\" :width 12 :height 12 :tooltip \"$w\" :onclick \"i3 workspace $w\" \"$w\")"
# done
# printf ")\n"
