
g++ -o lux_wendroff lux_wendroff.cc
./lux_wendroff
cd ./output
 convert -layers optimize -loop 0 -delay 50 0000.jpg -delay 10 *.jpg anime.gif
cd ../
