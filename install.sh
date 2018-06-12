#Install curl
sudo apt-get install autoconf automake libtool nroff perl
git clone https://github.com/curl/curl.git
cd curl
./buildconf
./configure
make
sudo make install

#Install Tidy
cd ..
git clone https://github.com/htacg/tidy-html5.git
cd tidy-html5
cd build/cmake
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make
sudo make install

#Install rapidxml
sudo apt-get install librapidxml-dev

#Make the source code
cd ../../..
cd RSS/src
make

#Create link to chronos
sudo apt-get install cron
cd ..
mv run.sh /etc/cron.hourly
cd ..
mkfile crontab
echo "$[RANDOM%59] * * * * /etc/cron.hourly/run.sh" >> cron.hourly