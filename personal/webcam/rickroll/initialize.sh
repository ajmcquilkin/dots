#! /bin/bash

# Start mocked audio and video drivers

sudo modprobe v4l2loopback devices=1 exclusive_caps=1 video_nr=5 card_label="Mocked Webcam"
sudo modprobe snd_aloop

echo -e "Initialized..."

# Start playback

ffmpeg -stream_loop -1 -re -i ~/Downloads/test.mp4 -map 0:v -vcodec rawvideo -pix_fmt yuv420p -f v4l2 /dev/video5 -map 0:a -f alsa hw:1,1
echo -e "Shutting down..."
