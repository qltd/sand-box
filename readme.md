#sand-box
###Getting Started (a short guide to a Drupal/GitHub development workflow)

#####Obtaining a copy of the repository
Create a local directory for the project. It is a good practice to make this directory a child of another directory that specifies an environment; for example, when planning to pull the `dev branch` you could create a folder called `dev` in your web root, to which the project folder `sand-box` could be a child. Do this within your preferred UI, or by issuing the following commands.
 
Replace `/web/root/` with your webroot

```
cd /web/root/
mkdir -p dev/sand-box
```

If you do not have permission to write in your web root, but you do have sudo access, issue the following commands instead of `mkdir -p dev/sand-box`.

Replace `user` and `group` with your system username and group; if you don't want to specify a group, you can omit `:group` from the `user:group` syntax

```
sudo mkdir -p dev/sand-box
sudo chown -R user:group dev	
```

Next, initiate and pull from the repository.

```
cd dev/sand-box
git init
git remote add origin git@github.com:qltd/sand-box.git
git pull origin dev
```

That's it. Now you have local copy of the `dev branch`. Note that you could change `dev` at the end of `git pull origin dev` to be any branch that you would like.

#####Creating a local database

Create a local `dev database` with phpMyAdmin or by issuing the following command.

Replace `username` with the username of a local MySQL admin account

```
mysqladmin -u username -p create sand_box_dev
```
If you are not using phpMyAdmin, log in to MySQL 

Replace `username` with the username of a local MySQL admin account

```
mysql -u username -p
```
Grant a user by the name of `sand_box_user` the permissions required by Drupal. Use phpMyAdmin, or the following command while logged into a MySQL admin account. Note that the mixed use of both ' and ` is deliberate and should not be modified.

Replace `password`

```
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER, LOCK TABLES, CREATE TEMPORARY TABLES 
ON `sand_box_dev`.* TO 'sand_box_user'@'localhost' IDENTIFIED BY 'password';

FLUSH PRIVILEGES;
```

#####Configuring Drupal

By default, `settings.php` is ignored by git, so we need to copy (NOT rename) `default.settings.php` to `settings.php`. This can be done through your preferred UI, or by issuing the following command from the root directory of the project.

```
cp sites/default/default.settings.php sites/default/settings.php
```

We also need to change the permissions of the these files to be accessible to Drupal. Do NOT make the second command recursive.

```
chmod 777 sites/default/settings.php
chmod 777 sites/default
```

Now, navigate to the location of site in your browser and follow the instructions for a standard installation. An important note is that a lot of what you enter will be disregarded once you pull a copy of the database downstream using the `Backup and Migrate` module, including user login information.

```
http://localhost/dev/sand-box		or whatever your URL is
```

Finally, you shouldn't forget to restore the previous permissions to the Drupal site settings file and folder.

```
chmod 644 sites/default/settings.php
chmod 755 sites/default
```

#####Pulling the latest copy of the database downstream

Two guiding principles for data migration:

1. Non-test content should always be added to the `live`, or most live-like, version of the site that currently exists.
2. Content should migrate downstream, from `live` to `test` to `dev`; or from `test` to `dev` if `live` does not yet exist.

With that in mind, we can download a copy of the most live-like database from `test` by visiting the following URL and clicking `Backup now`.

```
http://sand-box.qltdclient.com/admin/config/system/backup_migrate
```

- Select the following options: Backup from `Default Database` to `Manual Backups Directory` using `Default Settings`
- Download the backup by clicking the `download` link in the Drupal alert message
- You can select `Download` instead of `Manual Backups Directory` for the second option, but an abundance of stored backups is never a bad idea

Now we can migrate data by uploading the file we just downloaded to our development environment at the following URL.

Replace `localhost/dev/sand-box` with the correct URL for your dev site

```
http://localhost/dev/sand-box/admin/config/system/backup_migrate/restore
```

If there are additional files associated with the content that is being migrated downstream, that content will need to be copied separately. It is common to use a script for this task.

```
<?php

// I will create a script, and add its contents here
// Before that happens, I want to introduce authorized 
// ssh keys in a future subsection of this document

?>
```

#####Staying Current

Pull

```
git pull origin dev
```

#####Pushing features upstream

…

###Additional Considerations

- Global Admin Account Information

	- User:		admin
	
	- Pass:		qltd109

- Site images should be stored in the selected theme's subdirectory. Anything stored in '/sites/default/files' will be ignored during git transactions (per '.gitignore')
