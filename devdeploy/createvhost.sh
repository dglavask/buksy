# This script sets your developement enviroment
# Preconditions: Apache2, mysql, php5 installed
# Tested on Ubuntu 15
sudo mkdir -p /var/www/buksy.dev/public_html
sudo chown -R $USER:$USER /var/www/buksy.dev/public_html
sudo cp index.html /var/www/buksy.dev/public_html/
sudo echo "# Added by the buksy dev deploy script for setting a apache virtual host" >> /etc/hosts
sudo echo "127.0.0.1 www.buksy.dev buksy" >> /etc/hosts
sudo cp buksy.dev.conf /etc/apache2/sites-available/
sudo a2ensite buksy.dev.conf
sudo service apache2 reload
