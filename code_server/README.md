# How to run the server?

To run the server, you will need two things: a web server and a SQL database. 
For the web server, you can use eighter _Apache_ or _Nginx_ and set it up as a 
proxy to localhost:3000 and redirect the traffic to our custom link 
http://ipAdress/4bits. For the database, you will need to have an instance of 
_MySQL_ installed and running on your system.

You can avoid the server and database installation by downloading _MAMP_ or _XAMPP_ 
because eighter has an  _Apache_ and a SQL database installed. We recommend using 
_MAMP_ because it is the only one we could configure as a proxy in this tutorial. 
So if you want to use _XAMPP_, the only solution we can give you is to stop the 
_Apache_ process and use our configured _Nginx_ server that we provide in this 
repository.

You can find guides on how to set up _MAMP_ and _XAMPP_ in this document.

## Running the app
You will need to have [node.js](https://nodejs.org/en/) installed on your computer.

Once installed, navigate to the `code_server` directory where the file _index.js_ 
is . Then, run
```
node . 
```
on the command prompt.

## XAMPP configuration
As we won't be using _Apache_ for this one, we will have trouble visualizing our 
database as we won't have access to _phpMyAdmin_ while the server is running.

First, navigate to the following path relative to the project directory:
```
\code_server\nginx_server
```

The server you will be running is already configured to work by using the `start` 
and `stop` commands, but here is the full documentation:

### Starting and stopping the server
```
start nginx
nginx -s stop
```
### Listing the running processes and force quiting (on windows)
```
@tasklist /fi "imagename eq nginx.exe"
@taskkill /f /im nginx.exe
```
### Others 
```
nginx -s quit                 // Stoping the server... Also... I think...
nginx -s reload               // Restarting the server
nginx -s reopen               // Restarting the server... As well???
```

![](../__assets/xamppSetup.jpg)

Then, on _XAMPP_, you may start only the _MySql_ process, and the app should work 
correctly with the database. Given you endered your credentials right on the 
_index.js_ file.

## MAMP configuration
---
![](../__assets/mampRoute.jpg)

Locate your _MAMP_ installation folder and navigate to:
```
\conf\apache
```

![](../__assets/confRoute.jpg)

Here we will find the `httpd.conf`, open it with any text editor and paste the
following configuration almost at the end of the file.
```
<VirtualHost *:80>
	ProxyPass /4bits http://localhost:3000/
	ProxyPass /api http://localhost:3000/api
</VirtualHost>
```
![](../__assets/config.jpg)

We don't think it matters if you paste it anywhere on the file, but to be safe, use the photo above to guide yourself on where to put it

Now, open _MAMP_ and run the node app.
