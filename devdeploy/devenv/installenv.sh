#!/bin/bash
# This script will install gvim with all plugins, llvm, and a default web browser
# TODO: Check if the following programs are installed:
# - gvim
# - screen
# - browser
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
screen_conf="$DIR/devscreenrc"
num_of_monitors=$(xrandr -q | grep -w connected | wc -l)

echo $screen_conf

if [ $num_of_monitors -eq 1 ]
then
	echo "Number of connected monitors is $num_of_monitors"
	echo -n "Select a working directory and press [ENTER]:"
	read -e working_dir
	working_dir=${working_dir//\~/$HOME}
	if [ -d "$working_dir" ]
	then
		echo "Using $working_dir as working directory."
		#cd $working_dir
		sensible-browser &
		gnome-terminal  --full-screen --working-directory=$working_dir -e "screen -c $screen_conf" --title="DEVELOPEMENT" &
	else
		echo "Invalid directory! Terminating script, please start again."
	fi	
elif [ $num_of_monitors -eq 2 ]
then
	echo "Number of connected monitors is $num_of_monitors"
else
	echo "This mode is not supported curently"
fi

