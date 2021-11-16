#! /usr/bin/python
# Source: https://github.com/CH4ND4N-x/i3gaps/blob/master/polybar/music
# Image command: feh "$(playerctl metadata --format "'{{mpris:artUrl}}'" | cut -c 9- | rev | cut -c 2- | rev)"

import time
import subprocess

FONT_INDEX = 1
UPDATE_DELAY = 0.3

MAX_TITLE_LEN = 54 # 27
MAX_ARTIST_LEN = 36 # 18

def substring(curr, limit):
	return (curr[:limit] + "...") if len(curr) > limit else curr

def get_playerctl_meta(field, length):
	field_process = subprocess.run(["playerctl", "metadata", "--format", "'{{" + field + "}}'"], capture_output = True)
	field = [x.decode("utf8") for x in field_process.stdout.split(b"\n") if len(x)]
	return "" if not field else substring(field[0][1:-1], length)

def get_playerctl_status():
	status_process = subprocess.run(["playerctl", "status"], capture_output = True)
	return "Playing" in str(status_process.stdout)

def print_info(info):
	print("%%{T%d}" % (FONT_INDEX) + info + " %{T-}", flush=True)

# def print_info(*argv):
# 	print("%%{T%d}" % (FONT_INDEX) + " - ".join(argv) + " %{T-}", flush=True)

def main():
	title = get_playerctl_meta("title", MAX_TITLE_LEN)
	artist = get_playerctl_meta("artist", MAX_ARTIST_LEN)
	# playing = "" if get_playerctl_status() else ""
	playing = "Playing" if get_playerctl_status() else "Paused"

	if not title or not artist:
		print("")
	else:
		print("[{}] {} ({})".format(playing, title, artist))

if __name__ == "__main__":
	main()
