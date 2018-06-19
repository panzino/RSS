# RSS

RSS is a tool designed for price conscious consumers. It's designed to automatically alert the user via email about price drops on watched products.

___
## Building RSS

1. Download the latest source from the Git server: 
	```
   git clone https://github.com/panzino/RSS.git
	```
2. Enter RSS source directory:
	```
   cd RSS
	```
3. Change install script permission:
	```
   chmod 744 install.sh
	```
4. Run the install script:
	```
   sudo ./install.sh
	```
	
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

There are two user-configured files that must be set before RSS can function:   
   [settings.txt][1]  
   [http_search_list.txt][2]  


### settings.txt
<dl>
  <dt>Definition &nbsp; &nbsp; &nbsp; list </dt>
  <dd>Is something people use sometimes.</dd>

  <dt>Markdown in HTML</dt>
  <dd>Does *not* work **very** well. Use HTML <em>tags</em>.</dd>
</dl>


*Example file:*  
   *1* &nbsp; &nbsp; [3]
   *2* &nbsp; &nbsp; [feedOne]  
   *3*		 url = https://www.ebay.com/sch/i.html?_nkw=f3-1600c9d-16grsl&_sop=15  
   *4*		 item = 1600  
   *5*		 ext = html  
   *6*		 price = 80  
   *7*		 [feedTwo]  
   *8*		 url = https://www.newegg.com/Product/RSS.aspx?Submit=Property&N=100007609%20600006178%20600213067%20600564396%20600006157&IsNodeId=1&ShowDeactivatedMark=False  
   *9*		 item = 1600  
   *10*		 ext = xml  
   *11*		 price = 1000  

### http_search_list.txt


### other files

	


___
## Operating Systems

This software is currently only designed for UNIX systems. Windows support might eventually be added. It is designed to run on small servers: Raspberry Pi, Orange Pi, et al. 

* Ubuntu 18.04
* Armbian 5.38

Other UNIX systems might support this software. These are the environments that are currently proven to work.

___
## Version Log

1. 6/19/2018  
   Software and test-suite are functional but not user-friendly. Future versions will aim to increase usability

___
## Dependencies

  - [Tidy-HTML5][3]  
  - [Curl][4]  
  - [Rapidxml][5]  


[1]: settings.txt
[2]: http_search_list.txt
[3]: https://github.com/htacg/tidy-html5
[4]: https://github.com/curl/curl
[5]: http://rapidxml.sourceforge.net/manual.html