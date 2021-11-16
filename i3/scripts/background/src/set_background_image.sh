#! /bin/bash

if [[ -p /dev/stdin ]]; then # Check stdin
	url="$(cat -)"
elif [[ -n $1 ]]; then # Check first argument
	url="$1"
else
	echo "Image URL is a required field"
	exit 1
fi

# Back up previous background
cp ~/Background/default.jpg /tmp/background_temp.jpg
feh --bg-fill /tmp/background_temp.jpg -q

# Download and save new background
curl -o ~/Background/default.jpg -L "$url"

# Update terminal theme
wal -c
wal --saturate 0.4 -i ~/Background/default.jpg -b 181818 -q &
