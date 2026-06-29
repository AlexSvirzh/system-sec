#!/bin/bash

echo "ProcessCount" > log.txt
echo "Logging process count"

while true; do
    ps -e | wc -l >> log.txt
    sleep 0.2
done
