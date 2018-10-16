if (!exists("file_in")) file_in='maze512-1-0.log'
if (!exists("file_out")) file_out='maze512-1-0.png'
if (!exists("file_id")) file_id='id_line.dat'

set style line 1 linetype 2 linecolor rgb '#ff0000' linewidth 3

set pm3d map
set terminal png 
set output file_out



# set palette defined ( 20 "#101010", 30 "#ff0000", 40 "#00ff00", 50 "#e0e0e0" ) 

set palette defined ( 0 "white", 1 "blue", 2 "green", 3 "orange", 4 "red") 


set xrange[0:9000]
set cbrange [.0:0.5]


splot file_in, \
      file_id with lines linestyle 1 notitle

