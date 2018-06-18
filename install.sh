#Install curl
apt-get install autoconf automake libtool
git clone https://github.com/curl/curl.git /home/$(logname)/curl
cd ..
cd curl
./buildconf
./configure
make
make install

#Install Tidy
git clone https://github.com/htacg/tidy-html5.git /home/$(logname)/tidy
cd tidy
cd build/cmake
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make
sudo make install

#Install rapidxml
apt-get install librapidxml-dev

#Make the source code
cd ..
cd ..
cd ..
cd RSS/src
make

#Create link to chronos
sudo apt-get install cron
cd ..
mv run.sh /etc/cron.hourly
cd ..
mkfile crontab
echo "$[RANDOM%59] * * * * /etc/cron.hourly/run.sh" >> cron.hourly