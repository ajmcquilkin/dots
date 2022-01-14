#! /bin/bash

xprop -spy -root _NET_CURRENT_DESKTOP | sed "s/.* = //"