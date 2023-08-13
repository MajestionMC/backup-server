#!/bin/bash

binary_list=$(crontab -l | grep -o -E '/[^ ]+')

for binary in $binary_list; do
	if ! which "$binary" &> /dev/null; then
		echo "Binary "$binary" not found. Removing corresponding cron jobs..."
		crontab -l | grep -v "$binary" | crontab -
		echo "Cron jobs for "$binary" removed."
	fi
done