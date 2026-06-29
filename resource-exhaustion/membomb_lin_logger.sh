#!/bin/bash

OUTPUT_FILE="memory_usage.csv"
echo "Timestamp,FreeMemory_MB" > "$OUTPUT_FILE"
echo "Starting memory monitoring..."

while true; do
    TIMESTAMP=$(date +%H:%M:%S)
    FREE_MEM=$(free -m | awk 'NR==2{print $4}')
    echo "$TIMESTAMP,$FREE_MEM" >> "$OUTPUT_FILE"
    sleep 2
done
