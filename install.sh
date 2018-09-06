#1. INSTALL DEPENDENCIES

#Install curl from source
apt-get install autoconf automake libtool make cmake gcc g++
git clone https://github.com/curl/curl.git /home/$(logname)/curl
cd ..
cd curl
./buildconf
./configure
make
make install
cd ..

#Install Tidy from source
git clone https://github.com/htacg/tidy-html5.git /home/$(logname)/tidy
cd tidy
cd build/cmake
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make
sudo make install

#Install rapidxml
apt-get install librapidxml-dev
cd /usr/include/rapidxml
mv rapid* /usr/local/include
#------------------------------------------------------

#2. Make RSS source code
cd ..
cd ..
cd ..
cd price_tracker/src
make
#------------------------------------------------------

#3. Create cron job
sudo apt-get install cron
cd ..
mv run.sh /etc/cron.hourly
cd /etc
echo -n $(shuf -i 0-60 -n 1) >> crontab
echo " * * * *" $(logname)  "/etc/cron.hourly/run.sh" >> crontab
#------------------------------------------------------

#4. User entered email information
echo "Please enter a gmail account to send email from"
read fromEmail
echo "Please enter the password for the gmail account"
read passwordEmail
echo "Please enter an email address to send email to"
read toEmail

echo "FROM=$fromEmail" >> /etc/environment
echo "RSSPass=$passwordEmail" >> /etc/environment
echo "TO=$toEmail" >> /etc/environment


#I'd like to apologize for the below solution...
#    I couldn't find a way of using a C++ macro and drawing the 
#    environment variable into the preexisting code
echo "#define FROM \"< $fromEmail >\"" | cat - /home/$(logname)/price_tracker/src/email.cpp > temp && mv temp /home/$(logname)/price_tracker/src/email.cpp
echo "#define TO \"< $toEmail >\"" | cat - /home/$(logname)/price_tracker/src/email.cpp > temp && mv temp /home/$(logname)/price_tracker/src/email.cpp
echo "#define CC \"< $toEmail >\"" | cat - /home/$(logname)/price_tracker/src/email.cpp > temp && mv temp /home/$(logname)/price_tracker/src/email.cpp



echo "Set up complete!"
#------------------------------------------------------

