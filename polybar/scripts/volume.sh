#! /bin/bash
# Source: https://unix.stackexchange.com/questions/89571/how-to-get-volume-level-from-the-command-line

volume=$(awk -F"[][]" '/Left:/ { print $2 }' <(amixer sget Master))
volume_val=${volume:0:${#volume}-1}
icon=""

$(amixer get Master | grep -q '\[on\]')
is_muted="$?"

if (("$is_muted" == 1)); then
	icon=""
elif (("$volume_val" < 20)); then
	icon=""
elif (("$volume_val" < 50)); then
	icon=""
else
	icon=""
fi

echo "$icon $volume"
