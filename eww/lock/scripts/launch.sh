#! /bin/bash

eww --config $HOME/.config/eww/lock open-many lockLeft lockRight
eww --config $HOME/.config/eww/lock update tasks="$($HOME/.config/eww/lock/scripts/get_todo_list.sh)"