#!/bin/bash

while sleep 2
do
    ps aux | grep 'slave'
    if [ "$?" != "0" ]; then
        nohup slave -f > /dev/null 2>&1 &
    fi
done
