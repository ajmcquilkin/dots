#! /bin/bash

eww="$HOME/GitHub/eww/target/release/eww"

# Parameter Validation

if [[ -z "$1" ]]; then
  echo "Requested bluetooth state required" 1>&2
  exit 1
fi

if [[ -z "$2" ]]; then
  echo "EWW variable required" 1>&2
  exit 1
fi

if [[ -z "$3" ]]; then
  echo "Configuration directory required" 1>&2
  exit 1
fi

# Logic

if [[ "$1" = "on" ]]; then
  echo "Turning bluetooth on"
  sudo systemctl start bluetooth
  sudo rfkill unblock bluetooth
  $eww -c $3 update "$2=true"
  echo "Turned bluetooth on"
elif [[ "$1" = "off" ]]; then
  echo "Turning bluetooth off"
  sudo rfkill block bluetooth
  sudo systemctl stop bluetooth
  $eww -c $3 update "$2=false"
  echo "Turned bluetooth off"
else
  echo "Invalid bluetooth state (\"on\" or \"off\")"
fi
