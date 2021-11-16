#! /bin/bash

progress="$(curl -s -H "Authorization: Bearer 58BD5C0DC8D5433AB02CB08968750FB2" 192.168.10.178/api/job | jq .progress.completion)"
[[ ! -z "$progress" ]] && printf " %0.2d.%0.2s%%\n" ${progress%.*} ${progress##*.}
