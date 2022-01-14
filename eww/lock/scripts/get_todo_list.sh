#! /bin/bash

todoist --csv list | $HOME/.config/eww/lock/scripts/parse_tasks.out 5 5

# tasks="$(todoist list)"
# echo $tasks
