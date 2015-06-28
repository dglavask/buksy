#!/bin/bash
# This script is used to copy your local development files to the 
# The script should always start from the script folder ( currently it's root is the directory from which the script was called ).

sudo cp ../php/* /var/www/buksy.dev/public_html/ 

echo "The deploy folter now looks like":
ls -l -a -R /var/www/buksy.dev/public_html/
