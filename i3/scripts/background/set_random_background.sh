#! /bin/bash

script_dir=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")
cd "$script_dir"

node src/get_random_image.js | bash src/set_background_image.sh
