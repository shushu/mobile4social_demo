#!/bin/bash

# Modify the MySQL settings below so they will match your own.
MYSQL_USERNAME="root"
MYSQL_PASSWORD="root"
MYSQL_HOST="localhost"
MYSQL_DB_NAME="mobile4social_demo"

# Modify the login details below to be the desired login details for the Administrator account.
ADMIN_USERNAME="admin"
ADMIN_PASSWORD="admin"
ADMIN_EMAIL="admin@example.com"

# Set the base url of the site address.
BASE_DOMAIN_URL="http://localhost/mobile4social_demo/www"

# Modify Goole Cloud Messaing information
GCM_SENDER_ID=123456
GCM_API_KEY=654321

chmod 777 www/sites/default
rm -rf www/
mkdir www

bash scripts/build

cd www

drush si -y mobile4social_demo --account-name=$ADMIN_USERNAME --account-pass=$ADMIN_PASSWORD --account-mail=$ADMIN_EMAIL --db-url=mysql://$MYSQL_USERNAME:$MYSQL_PASSWORD@$MYSQL_HOST/$MYSQL_DB_NAME --uri=$BASE_DOMAIN_URL mobile4social_demo_migrate_content.dummy_content=TRUE
drush vset gcm_sender_id $GCM_SENDER_ID
drush vset gcm_api_key $GCM_API_KEY

# These commands migrates dummy content and is used for development and testing. Comment out both lines if you wish to have a clean mobile4social_demo installation.
drush mi --all --user=1

# This command does the login for you when the build script is done. It will open a new tab in your default browser and login to your project as the Administrator. Comment out this line if you do not want the login to happen automatically.
drush uli --uri=$BASE_DOMAIN_URL
