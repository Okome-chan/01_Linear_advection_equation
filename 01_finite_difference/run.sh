
g++ -o finite_difference finite_difference.cc
./finite_difference
cd ./output
 convert -layers optimize -loop 0 -delay 50 0000.jpg -delay 10 *.jpg anime.gif
cd ../
