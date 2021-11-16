#! /bin/bash

# Reference: https://github.com/haotongye/dotfiles/blob/master/bin/lock

# ---- images ---- #

in_image=~/Background/lock.jpg
out_image=~/Background/lock.png

# ---- colors ---- #

bg_color=E6EFF7FF

text_color=FFFFFFFF
ring_color=FFFFFFFF
inside_color=00000066
line_color=FFFFFF00
separator_color=AAAAAAFF

modif_color="$text_color"

verif_color="$text_color"
ring_ver_color="$ring_color"
inside_ver_color="$inside_color"

wrong_color="$text_color"
ring_wrong_color="$ring_color"
inside_wrong_color="$inside_color"

key_hl_color=00FF00FF
bs_hl_color=FF0000FF

# ---- configuration ---- #

# if [ ! -f "$out_image" ]; then
# 	convert $in_image $out_image
# fi

# ---- command ---- #

# loginctl lock-session

i3lock -i $out_image --scale --ignore-empty-password --clock --indicator --color="$bg_color" \
	--time-color="$text_color" --time-str="%I:%M:%S %p" \
	--date-color="$text_color" --date-str="%A, %B %d, %Y" \
	--pass-media-keys --pass-power-keys --pass-screen-keys \
	--ring-width=2.0 --radius=144 --ring-color="$ring_color" --separator-color="$separator_color" \
	--inside-color="$inside_color" --line-color="$line_color" --separator-color="$separator_color" \
	--separator-color="$separator_color" \
	--verif-color="$wrong_color" --ringver-color="$ring_ver_color" --insidever-color="$inside_ver_color" --verif-text="Validating..." \
	--wrong-color="$wrong_color" --ringwrong-color="$ring_wrong_color" --insidewrong-color="$inside_wrong_color" --wrong-text="Invalid Auth" \
	--keyhl-color="$key_hl_color" --bshl-color="$bs_hl_color" --noinput-text="Empty" \
&& echo mem > /sys/power/state
