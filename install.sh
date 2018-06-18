#Install curl
#apt-get install autoconf automake libtool make cmake gcc g++
#git clone https://github.com/curl/curl.git /home/$(logname)/curl
#cd ..
#cd curl
#./buildconf
#./configure
#make
#make install
#cd ..

#Install Tidy
#git clone https://github.com/htacg/tidy-html5.git /home/$(logname)/tidy
#cd tidy
#cd build/cmake
#cmake ../.. -DCMAKE_BUILD_TYPE=Release
#make
#sudo make install

#Install rapidxml
#apt-get install librapidxml-dev
#cd /usr/include/rapidxml
#mv rapid* /usr/local/include

#Make the source code
#DONE
cd ..
cd ..
cd ..
cd RSS/src
make

#Create link to chronos
sudo apt-get install cron
cd ..
mv run.sh /etc/cron.hourly
cd /etc
echo -n $(shuf -i 0-60 -n 1) >> crontab
echo " * * * *" $(logname)  "/etc/cron.hourly/run.sh" >> crontab
