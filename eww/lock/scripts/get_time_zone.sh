#! /bin/bash

timedatectl | gawk -F': ' ' $1 ~ /Time zone/ {print $2}'
