#!/bin/sh
xset -dpms # disable DPMS (Energy Star) features.
xset s off # disable screen saver
xset s noblank # don't blank the video device
unclutter &
matchbox-window-manager &
midori -e Fullscreen -a http://127.0.0.1:80/index.php
