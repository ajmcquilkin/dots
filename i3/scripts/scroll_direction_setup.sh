#! /bin/bash
# Source: https://coderwall.com/p/eu5s6w/set-all-mouse-input-device-to-use-natural-scrolling

xinput list | egrep "slave.*pointer" | grep Mouse | grep -v XTEST | sed -e 's/^.*id=//' -e 's/\s.*$//' | xargs -IMouse sh -c 'echo "Setting mouse Mouse"; xinput get-button-map Mouse | tr " " "\n" | sort -g | xargs | sed "s,4 5,5 4,g" | sed "s,6 7,7 6,g" | xargs -i sh -c "xinput set-button-map Mouse {}; echo {};"' > /dev/null
xinput list | egrep "slave.*pointer" | grep Touchpad | grep -v XTEST | sed -e 's/^.*id=//' -e 's/\s.*$//' | xargs -IMouse sh -c 'echo "Setting mouse Mouse"; xinput get-button-map Mouse | tr " " "\n" | sort -g | xargs | sed "s,4 5,5 4,g" | sed "s,6 7,7 6,g" | xargs -i sh -c "xinput set-button-map Mouse {}; echo {};"' > /dev/null
