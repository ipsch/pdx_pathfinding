#!/bin/bash

for log_file in ./benchmark/*.log;
	do 
	#echo "$log_file";
	#echo ${log_file/.log/.png}
	gnuplot -e "file_in='$log_file'; file_out='${log_file/.log/.png}'; file_id='./benchmark/id_line.dat'" ./benchmark/runtime.pl
done