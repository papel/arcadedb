#!/bin/bash

for name in `cat lista.txt`; do
    if [[ -e roms/$name'.zip'  ]]; then
        mv roms/$name'.zip' nons
    else
        echo 'error: '$name
    fi
done
