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
## Updating RSS

DO NOT RUN THE INSTALL SCRIPT WHEN UPDATING!

1. Save your settings.txt and http_search_list.txt files

2. Download the latest source from the Git server:
   ```
   git clone https://github.com/panzino/RSS.git
   ```
3. Enter the RSS directory and src subdirectory
   ```
   cd RSS/src
   ```
4. Build the new source material
   ```
   make
   ```
5. Copy your settings.txt and http_search_list.txt files into the RSS directory

___
## Configuring RSS

There are two user-configured files that must be set before RSS can function: [settings.txt][100] and [http_search_list.txt][105]   


### settings.txt

This file designates the products that the consumer is watching for price drops. It holds four descriptors: *url*, *item*, *ext*, and *price*. These four descriptors form one *feed*. One *feed* is for one item you are price watching. Multiple *feeds* are expected. These will be covered later

*Example file*  
   *1* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [2]  
   *2* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [feedOne]    
   *3* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; url = https://www.amazon.com/s?url=search-alias%3Daps&field-keywords=light+bulbs  
   *4* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; item = light_bulbs  
   *5* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ext = html  
   *6* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; price = 20  
   *7* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [feedTwo]  
   *8* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; url = https://www.newegg.com/Product/RSS.aspx?Submit=Property&N=100007609%20600006178%20600213067%20600564396%20600006157&IsNodeId=1&ShowDeactivatedMark=False  
   *9* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; item = 1600  
   *10* &nbsp; &nbsp; &nbsp; &nbsp; ext = xml  
   *11* &nbsp; &nbsp; &nbsp; &nbsp; price = 1000  




| Line     | Strongly Formatted* | Description                                                                 | Example              |
| -------- |:-------------------:| :---------------------------------------------------------------------------| :--------------------|
| 1 | yes | Indicates how many items you are watching. This number must be correct and must be typed in this format: `[x]` | In this example we are watching 2 items |
| 2 | no | Just a title for the next four lines. So you know which four descriptors belong together | In this example, this is our first feed |
| 3 | yes | This is the first of our four descriptors. This is the URL to the webpage that contains the search you want this code to run. This code is not smart and you have to specify where to look for a product you want to price watch for. Improper search results can lead to *stream pollution* which will be covered later. Ensure the `url = ` is preserved. The `=` must have a space on both sides | In this example we are running a search for light bulbs at Amazon |
| 4 | yes | This is the second of our four descriptors. This is the description of the product you are price watching for. The descriptor must be one word. Use underscores/*_* in place of spaces | In this example our descriptor is for *light bulbs* |
| 5 | yes | This is the third of our four descriptors. This is the file type of the source URL. In most cases this will be an HTML site. Unless you are using an RSS feed. In these cases choose *XML* as the parsing is faster. If you don't know which to pick choose *html* | In this example our website is an HTML site |
| 6 | yes | This is the last of our four descriptors. This is the price you want to watch this item for. If the online price is found to be lower than this price, you will be sent an email alert | In this example our price is $20 
| 7 - 11 | x | Lines for the next feed follow the same rules as for the first feed | This is solely included to provide an example with two feeds |

*Indicates format must be followed EXACTLY


### http_search_list.txt

This file designates where to look in the HTML webpages of URLs you are price watching on

*Example file*  
   *1* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Amazon: a-size-base a-color-base a-offscreen  
   *2* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Ebay: s-item__price   
   *3* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Walmart: aria-label  

Look through the source file [here][200] for a product that costs $12.99. You will find it next to an HTML tag named *a-offscreen*. Therefore, you must add that tag to this file in the appropriately named category. This tells the RSS source code where to look for the price tag in the HTML from Amazon. To add a different website follow the formatting in this file. Multiple tags are seperated by white space.

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
2. 9/12/2018
   Changed parser to string implementation, fixed install script, various bug fixes & performance improvements

___
## Dependencies

  - [Tidy-HTML5][110]  
  - [Curl][115]  

___
## Known Problems

* Problematic Websites: Walmart
* Any website displaying price using javascript


[100]: settings.txt
[105]: http_search_list.txt
[110]: https://github.com/htacg/tidy-html5
[115]: https://github.com/curl/curl
[200]: responses/examples/amazon_example.html