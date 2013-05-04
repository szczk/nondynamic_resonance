#reset
#set terminal pngcairo enhanced size 6000,700; 
#set out "plot.png";
#set xlabel "t"
#set ylabel "x(t)"
#set style line 1 lt 1 lc rgb "gray" lw 1
	 
#set title "x(t)";
#set yrange [-0.1:1.1];
#plot 1.0 ls 1,0.0 ls 1,'data.txt' using 1:2 with lines notitle lc rgbcolor '#000000';




reset

set terminal pngcairo enhanced size 2000, 1200; 
set out "signal.png";


set style line 1 lt 1 lc rgb "gray" lw 1
set style line 2 lt 1 lc rgb "red" lw 1

set multiplot layout 2,1

set lmargin screen 0.02
set rmargin screen 0.98
plot 0.0 ls 1 notitle, 1.0 ls 2 notitle,'signal.txt' using 1:2 with linespoints notitle lc rgbcolor '#000000';
set yrange [0:2]
plot 0.0 ls 1,'filtered.txt' using 1:2 with linespoints notitle lc rgbcolor '#000000';



unset multiplot


