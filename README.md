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
   [settings.txt][100]  
   [http_search_list.txt][105]  


### settings.txt

This file designates the products that the consumer is watching for price drops. It holds four descriptors: url, item, ext, and price. These will be covered later. 

*Example file*
   *1* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [3]  
   *2* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [feedOne]    
   *3* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; url = https://www.ebay.com/sch/i.html?_nkw=f3-1600c9d-16grsl&_sop=15  
   *4* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; item = 1600  
   *5* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ext = html  
   *6* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; price = 80  
   *7* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [feedTwo]  
   *8* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; url = https://www.newegg.com/Product/RSS.aspx?Submit=Property&N=100007609%20600006178%20600213067%20600564396%20600006157&IsNodeId=1&ShowDeactivatedMark=False  
   *9* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; item = 1600  
   *10* &nbsp; &nbsp; &nbsp; &nbsp; ext = xml  
   *11* &nbsp; &nbsp; &nbsp; &nbsp; price = 1000  

Going line by line:  




| Line | Strongly Formatted* | Description                                                                                                    |
| -----|:-------------------:| --------------------------------------------------------------------------------------------------------------:|
| 1    | yes                 | Indicates how many items you are watching. This number must be correct and must be typed in this format: `[x]` |
| 2    |                     |   $12                           |
| 3    |                     |    $1                           |


*Indicates the format must be followed EXACTLY


Line 1: Indicates how many items you are watching. This number must be CORRECT and must be typed in this format:  `[x]`





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

  - [Tidy-HTML5][110]  
  - [Curl][115]  
  - [Rapidxml][120]  


[100]: settings.txt
[105]: http_search_list.txt
[110]: https://github.com/htacg/tidy-html5
[115]: https://github.com/curl/curl
[120]: http://rapidxml.sourceforge.net/manual.html