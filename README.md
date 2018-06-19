# RSS

RSS is a tool designed for price conscious consumers. It's designed to automatically alert the user via email about price drops on watched products.

___
## Building RSS

0. This software is currently only designed for unix systems and is solely tested on Ubuntu and Armbian. 

1. Download the latest source from the Git server: 
	'''
	git clone https://github.com/panzino/RSS.git
	'''
2. Enter RSS source directory:
	'''
	cd RSS
	'''
2. Change install script permission:
	'''
	chmod 744 install.sh
	'''
2. Run the install script:
	'''
	sudo ./install.sh
	'''
	This will install the following packages and libraries:
	-autoconf
	-automake
	-libtool
	-make
	-cmake
	-gcc
	-g++
	-cron
	-curl
	-tidy-html5
	-rapidxml

3. Currently, RSS is automatically configured to run once per hour. 

___
## Configuring RSS

There are two user-configured files that must be set before RSS can function: [settings.txt] (../blob/master/settings.txt) 
[http_search_list.txt] (../blob/master/http_search_list.txt)

___
### settings.txt

This file lists th






___
## Version Log

1.0: Software and test-suite are functional but are not user-friendly. Future versions will aim to reduce complexity of use



___
## Dependencies

	- [Tidy-HTML5] (https://github.com/htacg/tidy-html5)
	- [Curl] (https://github.com/curl/curl)
	- [Rapidxml] (http://rapidxml.sourceforge.net/manual.html)