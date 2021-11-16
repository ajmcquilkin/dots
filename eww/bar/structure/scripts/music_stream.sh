#! /bin/bash

playerctl --follow metadata --format "{{mpris:artUrl}}" | sed -e '/^$/d' -e 's/^.\{7\}//'
