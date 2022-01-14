#! /bin/bash

nmcli radio wifi $1
eww --config $2 update wifiStatus="$(nmcli radio wifi)"
