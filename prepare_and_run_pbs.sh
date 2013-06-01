#! /bin/bash

#cd ~/mean_passages2/


if [ ${USER} = "ufszczep" ];
then
module add gcc/4.5.3
module add fftw

make -f makefile_zeus
else
make
fi


# /software/local/libs/FFTW/3.3.2/gnu/double-prec/include/
rm *.png
rm *.txt
touch jobs_ids.txt

tmpdir="/tmp/"
storagedir="./"
threads=1
# /mnt/lustre/scratch/people/ufszczep/
# /storage/ufszczep/

if [ ${USER} = "ufszczep" ];
then
  tmpdir="\/mnt\/lustre\/scratch\/people\/ufszczep\/"
# storagedir="\/storage\/ufszczep\/"
  storagedir="\/mnt\/lustre\/scratch\/people\/ufszczep\/output\/"

  threads=1
fi 

echo "tmp dir: '$tmpdir'"
echo "storage dir: '$storagedir'"


echo "\n"

# ${threads} --noise ${noise} --beta ${beta} --threshold ${threshold} --storage "${storage}" --tmp "${tmp}



for alpha in $(seq -w 0.5 0.01 2.0)
do
  for beta in 0.0  #$(seq -w -1.0 0.25 1.0)
  do
    for threshold in 1.5
      do
	  echo "alpha = $alpha, beta(skewness) = $beta, threshold = $threshold"
	  file="alpha_"$alpha"_beta_"$beta"_tresh_"$threshold".pbs"

		  if [ ${USER} = "ufszczep" ];
		  then
		    cat pbs_template.tpl | sed -e "s/\${tmp}/$tmpdir/g" -e "s/\${storage}/$storagedir/g" -e "s/\${alpha}/$alpha/g" -e "s/\${threshold}/$threshold/g" -e "s/\${beta}/$beta/g" -e "s/\${threads}/$threads/g" > $file
		    qsub -f $file >> jobs_ids.txt
		  else
		    ./main.x  --threads $threads --alpha $alpha --beta $beta --threshold $threshold --storage "$storage" --tmp "$tmp"
# 		    echo "plotting"
# 		    gnuplot "d_"$d"0_beta"$beta"_t100_plot.gnu"
		  fi
      done
    done

done



#text=$(tr '\n' ':' <jobs_ids.txt)

#qsub -W depend=afterok:$text  -f "plot_job.pbs"

# 0.5 0.7 0.9 1.1 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0 3.1 3.2 3.3 3.4 3.5 3.6 3.7 3.8 3.9 4.0 4.1 4.2 4.3 4.4 4.5
