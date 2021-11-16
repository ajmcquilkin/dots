#! /bin/bash

playerctl metadata --format "{{mpris:artUrl}}" | sed -e '/^$/d' -e 's/^.\{7\}//'
