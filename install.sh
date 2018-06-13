#Install curl
sudo apt-get install autoconf automake libtool
git clone https://github.com/curl/curl.git /home/$(logname)/curl
/home/$(logname)/curl/buildconf
/home/$(logname)/curl/configure
/home/$(logname)/curl make
sudo /home/$(logname)/curl make install

#Install Tidy
git clone https://github.com/htacg/tidy-html5.git /home/$(logname)
cd tidy-html5
cd build/cmake
/home/$(logname)/tidy-html5/built/cmake cmake ../.. -DCMAKE_BUILD_TYPE=Release
/home/$(logname)/tidy-html5/built/cmakemake
sudo /home/$(logname)/tidy-html5/built/cmake sudo make install

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