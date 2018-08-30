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