

script=plot.gnu

rm $script
touch $script


for alpha in $(seq -w 0.8 0.2 2.0)
do
  for beta in $(seq -w -1.0 0.25 1.0)
  do

	v=`printf "%1.2f" $beta`
	

	echo "\n\n" >> $script	  
	echo "reset" >> $script
	echo "set terminal pngcairo enhanced size 1200, 700;" >> $script 
	echo "set out \"results_a_"$alpha"_b_"$v".png\";" >> $script
	echo "set style line 1 lt 1 lc rgb \"gray\" lw 1" >> $script
	echo "set style line 2 lt 1 lc rgb \"red\" lw 1" >> $script
	echo "set title \"{/Symbol a} = "$alpha", {/Symbol b} = "$v"\"" >> $script
	echo "set xlabel \"{/Symbol s}\"" >> $script
	echo "set ylabel \"SNR\"" >> $script
	echo -n "plot " >> $script 

	

	for threshold in 1.0 1.1 1.2 1.3 1.4 1.5 
	do
	  echo "'alpha_"$alpha"0_beta_"$v"_thr_"$threshold"0_results.txt' using 1:2 with lp title 'tr="$threshold"',\\" >> $script
	done

	echo "'alpha_"$alpha"0_beta_"$v"_thr_2.00_results.txt' using 1:2 with lp title 'tr=2.0';" >> $script
	echo "\n" >> $script


    done

done

echo "drawing..."
gnuplot $script