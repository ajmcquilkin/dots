#! /bin/bash

# Reference: https://github.com/haotongye/dotfiles/blob/master/bin/lock

# ---- fonts ---- #

primary_font="Nasalization"
thin_accent_font="Graphie-Light"

# ---- images ---- #

# source_image=~/Background/lock_5.jpg
# source_image=~/Background/norbert-kowalczyk-PQHOmT-vkgA-unsplash.jpg
# source_image=~/Background/norbert-kowalczyk-ZE0X3vAnBvs-unsplash.jpg
# source_image=~/Downloads/striders_chilling_2.png
# source_image=~/Background/lock_4.jpg
# source_image=~/Background/planets/saturn.jpg
source_image=~/Background/jpegPIA23378-1.jpg

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

# ---- spacings ---- #

text_padding=60

time_size=60
time_date_spacing=15
date_size=42
date_greeter_spacing=21
greeter_size=21

confirm_size=21
line_height=2

# ---- helper functions ---- #

eww="eww --config $HOME/.config/eww/lock"

# ---- configuration ---- #

# if [ ! -f "$out_image" ]; then
# 	convert $in_image $out_image
# fi

# ---- main code ---- #

curr_monitor_dims="$(xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+x[0-9]+).*$/\1/')"

# ---- image conversion ---- #
# Reference: https://legacy.imagemagick.org/Usage/resize/
# Reference: https://stackoverflow.com/questions/21262466/imagemagick-how-to-minimally-crop-an-image-to-a-certain-aspect-ratio

# ---- subshell piping ---- #
# Reference: https://stackoverflow.com/questions/13107783/pipe-output-to-two-different-commands
# Reference: https://itectec.com/superuser/linux-execute-command-in-between-a-bash-pipe-row/

convert $source_image -geometry $curr_monitor_dims^ -gravity center -crop $curr_monitor_dims+0+0 RGB:- | \
tee >(i3lock --raw $curr_monitor_dims:rgb --image /dev/stdin -n \
	--pass-media-keys --pass-screen-keys --pass-power-keys \
	--ignore-empty-password --force-clock --bar-indicator --bar-max-height=$line_height --no-modkey-text \
	--ring-color=FFFFFFFF --inside-color=FFFFFFFF --keyhl-color=FFFFFFFF --bshl-color=FFFFFFFF \
	--bar-color=FFFFFF00 --verif-color=FFFFFFFF --wrong-color=FFFFFFFF --modif-color=FFFFFFFF \
	--verif-text="Verifying..." --wrong-text="Invalid Auth" --noinput-text="No Input" --lockfailed-text="Lock Failed" \
	--verif-font=$primary_font --wrong-font=$primary_font \
	--ringver-color=FFFFFF00 --ringwrong-color=FFFFFF00 \
	--greeter-size=$greeter_size --greeter-color=FFFFFFFF --greeter-align=1 --greeter-font=$primary_font \
	--time-str="%I:%M:%S %p" --time-color=FFFFFFFF --time-align=1 --time-font=$primary_font \
	--date-str="%a. %B %d, %Y" --date-color=FFFFFFFF --date-align=1 --date-font=$thin_accent_font \
	--time-size=$time_size --time-pos="$text_padding:h-$text_padding" \
	--date-size=$date_size --date-pos="$text_padding:h-$text_padding-$time_date_spacing-$date_size" \
	--greeter-text="I use Arch, btw" --greeter-pos="$text_padding:h-$text_padding-$time_date_spacing-$date_size-$date_greeter_spacing-$greeter_size"\
	--verif-align=2 --wrong-align=2 --modif-align=2 --ind-pos="w-$text_padding:h-$text_padding" --verif-size=$confirm_size --wrong-size=$confirm_size \
&& $eww close-all) > /dev/null \
&& $HOME/.config/eww/lock/scripts/launch.sh
