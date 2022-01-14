#! /bin/bash

# box_attrs="":orientation "h" :class "workspaces" :space-evenly true :halign "left" :valign "center" :hexpand true"

# Reference: https://stackoverflow.com/questions/1074450/sed-replace-part-of-a-line
# Reference: https://aweirdimagination.net/2020/08/16/reacting-to-active-window/
# Reference: https://stackoverflow.com/questions/918886/how-do-i-split-a-string-on-a-delimiter-in-bash

# IFS=', '
# xprop -spy -root _NET_DESKTOP_NAMES \
# | stdbuf -oL sed -nre 's/.* = (.*)/\1/gip' \
# | stdbuf -oL sed "s/\"//g" \
# | while read -ra LINE; do
#   active_workspace=`echo "$(xprop -root _NET_CURRENT_DESKTOP | stdbuf -oL sed -nre 's/.* = (.*)/\1/gip')+1" | bc`
#   printf "(box :orientation \"h\" :class \"workspaces\" :valign \"center\" :spacing 9"
#   for w in "${LINE[@]}"; do
#     printf "(button :class \"$([ $active_workspace = $w ] && echo 'workspace_active' || echo 'workspace')\" :width 12 :height 12 :tooltip \"$w\" \"$w\")" # :onclick `i3 workspace $w \$1> \/dev/null`
#   done
#   printf ")\n"
# done

xprop -spy -root _NET_CURRENT_DESKTOP | stdbuf -oL sed -nre 's/.* = (.*)/\1/gip' \
| {
  while read -ra ncd; do
    active_workspace=$(echo "$ncd+1" | bc)
    ws=`xprop -root _NET_DESKTOP_NAMES | stdbuf -oL sed -nre 's/.* = (.*)/\1/gip' | stdbuf -oL sed "s/\"//g"`

    IFS=', '
    read -a workspaces <<< "$ws"

    printf "(box :orientation \"h\" :class \"workspaces\" :halign \"start\" :valign \"center\" :spacing 9 "
    for w in "${workspaces[@]}"; do
      printf "(button :class \"$([ $active_workspace = $w ] && echo 'workspace_active' || echo 'workspace')\" :width 12 :height 12 :tooltip \"$w\" :onclick \"i3 workspace $w\" \"$w\")"
    done
    printf ")\n"
  done
}

