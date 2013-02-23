#sand-box
###Getting Started (a short guide to a Drupal/GitHub development workflow)

#####Obtaining a copy of the repository
Create a local directory for the project. Make sure this directory is a child of another directory that specifies its environment; for example, you could create a folder called 'dev' in your web root, within which the project folder 'sand-box' could live while in correspondence to the 'dev' branch on GitHub. Do this within your preferred UI, or by issuing the following commands.
 
- replace '/web/root/' with your webroot

<pre>
cd /web/root/
mkdir -p dev/sand-box
</pre>
Next, initiate and pull from the repository.
<pre>
cd dev/sand-box
git init
git remote add origin git@github.com:qltd/sand-box.git
git pull origin dev
</pre>
That's it. Now you have local copy of the 'dev' branch. Note that you could change 'dev' at the end of 'git pull origin dev' to be any branch that you would like.

#####Creating a local database

Create a local dev database with phpMyAdmin or by issuing the following command.

- replace 'username' with the username of a local MySQL admin account

<pre>
mysqladmin -u username -p create sand_box_dev
</pre>
If you are not using phpMyAdmin, log in to MySQL 

- replace 'username' with the username of a local MySQL admin account

<pre>
mysql -u username -p
</pre>
Grant a user by the name of 'sand_box_user' the permissions required by Drupal. Use phpMyAdmin, or the following command while logged into a MySQL admin account. Note that the mixed use of both ' and ` is deliberate and should not be modified.

- replace 'password'

<pre>
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER, LOCK TABLES, CREATE TEMPORARY TABLES 
ON `sand_box_dev`.* TO 'sand_box_user'@'localhost' IDENTIFIED BY 'password';

FLUSH PRIVILEGES;
</pre>

#####Configuring Drupal

By default, 'settings.php' does not travel through git, so we need to copy (NOT rename) 'default.settings.php' to 'settings.php'. This can be done through your preferred UI, or by issuing the following command from the root directory of the project.
<pre>
cp sites/default/default.settings.php sites/default/settings.php
</pre>
We also need to change the permissions of the these files to be accessible to Drupal. Do NOT make the second command recursive.
<pre>
chmod 777 sites/default/settings.php
chmod 777 sites/default
</pre>
Now, navigate to the location of site in your browser and follow the instructions for a standard installation. An important note is that a lot of what you enter will be disregarded once you pull a copy of the database downstream using the 'Backup and Migrate' module, including user login information.
<pre>
http://localhost/dev/sand-box		or whatever your URL is
</pre>
Finally, you shouldn't forget to restore the previous permissions to the Drupal site settings file and folder.
<pre>
chmod 644 sites/default/settings.php
chmod 755 sites/default
</pre>

#####Pulling the latest copy of the database downstream from 'test' or 'live'

Two guiding principles for data migration:

1. Non-test content should always be added to the 'live', or most live-like, version of the site that currently exists.
2. Content should migrate downstream, from 'live' to 'test' to 'dev'; or from 'test' to 'dev' if 'live' does not yet exist.

With that in mind, we can download a copy of the most live-like database from 'test' by visiting the following URL and clicking 'Backup now'.

- Select the following options: Backup from Default Database to Manual Backups Directory using Default Settings
- Download the backup by clicking the 'download' link in the Drupal alert message
- You can simply download the backup if you choose, but an abundance of stored backups is never a bad idea

<pre>
http://sand-box.qltdclient.com/admin/config/system/backup_migrate
</pre>

Now we can migrate data by uploading the file we just downloaded to our development environment at the following URL.

- Replace 'localhost/dev/sand-box' with the correct URL for your dev site

<pre>
http://localhost/dev/sand-box/admin/config/system/backup_migrate/restore
</pre>

#####Staying Current
Pull
<pre>
git pull origin dev
</pre>

#####Pushing features upstream

…

###Additional Considerations

- Global Admin Account Information

	- User:		admin
	
	- Pass:		qltd109

- Site images should be stored in the selected theme's subdirectory. Anything stored in '/sites/default/files' will be ignored during git transactions (per '.gitignore')
