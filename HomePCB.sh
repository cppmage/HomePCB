#! /bin/bash
# idea:
# -d || --drill do drill file;
# -c || --cut  do CutFile;# -s || --settings;
# -m || --mask do maskmaking
# -g || --grave do graving
# -t || --test whis testout
# -h || --help

#example:
#. build.sh -t -s  -d -g -c -m 

sudo chmod a+rw /dev/ttyUSB0

path=$(pwd)
count=1
pathtogfile=0
pathtodfile=0
testflag=0;
zdown=0;
wseed=0;
cspeed=0;
stty -F /dev/ttyUSB0 raw ispeed 9600 ospeed 9600 ignpar cs8 cstopb -echo   
#read n ;
#echo $n >> /dev/ttyUSB0
FSFS=$(cat $path/Settings.txt)
for part in $FSFS ;do
	if [ $count -eq 3 ];then
		pathgfile=$part	
	elif [ $count -eq 6 ];then 
		pathdfile=$part
	elif [ $count -eq 17  ];then
		wspeed=$part	
	elif [ $count -eq 21  ];then
		cspeed=$part	
	elif [ $count -eq 9  ];then
		zdown=$part	
	fi
		count=$((count+1))
done

echo "[PATHTOGRAVE]="$pathgfile
echo "[PATHTODRILL]=" $pathdfile
echo "[DWNSTEP]= $zdown mm"
echo "[WORKSPEED]= $wspeed mm/sec"
echo "[CUTSPEED]= $cspeed mm/sec"

#/***************************************************/
#########_Path_Create_##########
if [ -d $path/Release ];then : 
else
	mkdir $path/Release
	echo "  *[Directory: $path/Release was created]"
fi
################################
######_Settings_Write_##########
if [ -e $path/Settings.txt ] ;then :
	else 
	touch $path/Settings.txt
	echo "[PATHTOGRAVE]  =" >$path/Settings.txt
	echo "[PATHTODRILL]  =" >>$path/Settings.txt
	echo "[DWNSTEP] = 0 mm">>$path/Settings.txt
	echo "[HIGHT] = 0 mm">>$path/Settings.txt
	echo "[WORKSPEED] = 0 mm/sec">>$path/Settings.txt
	echo "[CUTSPEED] = 0 mm/sec">>$path/Settings.txt
	echo " *[File: $path/Settings.txt was created]"
fi
################################
#/***************************************************/
echo "|===============================|"
echo " *[CompilingGrave]           " | tr "\n" " "
#sudo 	c++ $path/Include/cvllib.cpp $path/Include/CVL.cpp -o ./Release/CreateVectorsList
	#c++ $path/Include/glib.cpp $path/Include/Graving.cpp -o ./Release/Graving
echo '+'
echo " *[CompilingCUT]             " | tr "\n" " "
#	c++ $path/Include/CutLine.cpp -o ./Release/CutLine
echo '+'
echo " *[CompilingMaskMaking]      " | tr "\n" " "
#	c++ $path/Include/MaskMaking.cpp -o ./Release/MaskMaking
echo '+'
echo " *[CompilingVectorsList]     " | tr "\n" " "
	c++ $path/Include/CVL.cpp $path/:qCreateVectorsList.cpp  -o ./Release/CreateVectorsList
echo '+'
echo " *[CompilingDrill]           " | tr "\n" " "
#	c++ $path/Include/Drilling.cpp -o ./Release/Drilling -lm
echo '+'
echo "|===============================|"
#/***************************************************/
while [ -n "$1" ];do 
case "$1" in
	-lc)
		echo "  [ $((10000/cspeed)) usleep]"
		#./Release/CutLine $path/VectorsList.txt 0.4 1.7 $((10000/cspeed)) 
		;;
	-d)
		#if [ $testflag -eq 1 ];then ./Release/Drilling $pathdfile $path/Settings.txt -t 			# void main(PathToRead,PathToReadSettingsFromFile,TESTMODE)
	 	#else ./Release/Drilling $pathdfile $path/Settings.txt			# void main(PathToRead,PathToReadSettingsFromFile)
		#fi
		;;
	--drill) 
		echo "  [ $((10000/cspeed)) usleep]" 
		#./Release/Drilling ~/thec/gerber/contetn/MFP/MFP-PTH.drl $path/Settings.txt
		;;
	-g) 
		###############_Creating_VectorsList###############	
			echo " *[CreatingVectorsList]      " | tr "\n" " " #void main(PathToReadFromFile,PathForWriteToFile)
			echo "+"	
		if [ $testflag -eq 1 ];then ./Release/Graving $path/VectorsList.txt  $zdown $((10000/wspeed)) -t		#void main(PathToVectorLists,TestMode,HightDown,Delay) 
		else echo "  [ $((zdown)) dwn  $((10000/wspeed)) usleep]"
				./Release/Graving $path/VectorsList.txt   $((zdown)) $((10000/wspeed))		#void main(PathToVectorLists,HightDown,Delay) 
		fi ;;
	--grave)
		###############_Creating_VectorsList###############	
			echo " *[CreatingVectorsList]      " | tr "\n" " "
			$path/Release/CreateVectorsList $pathgfile $path/VectorsList.txt 	#void main(PathToReadFromFile,PathForWriteToFile)
	#	if [ $testflag -eq 1 ];then
		 #	./Release/Graving $path/VectorsList.txt  $zdown $((10000/wspeed)) -t 			#void main(PathToVectorLists,mode,HightDown)
	 #	else
		 #	./Release/Graving $path/VectorsList.txt  $zdown $((10000/wspeed))   			#void main(PathToVectorLists,mode,HightDown)
	#	fi 
		;;	
	 -s) 
		###############_Write_to_Settings_#################
			: > $path/Settings.txt
			echo "[PATHTOGRAVE]  ="
				read pathtogfile
			echo "[PATHTOGRAVE]  = $HOME$pathtogfile" >$path/Settings.txt
			echo "[PATHTODRILL]  ="
				read pathtodfile
			echo "[PATHTODRILL]  = $HOME$pathtodfile" >>$path/Settings.txt
			echo "[HIGHT] = "
				read hight
			echo "[HIGHT] = $hight mm">>$path/Settings.txt
			echo "[SPEED] = "
				read speed
			echo "[SPEED] = $speed mm/sec">>$path/Settings.txt
		 ;;
	--settings) 
			: > $path/Settings.txt
			echo "[PATHTOGRAVE]  ="
				read pathtogfile
			echo "[PATHTOGRAVE]  = $pathtogfile" >$path/Settings.txt
			echo "[PATHTODRILL]  ="
				read pathtodfile
			echo "[PATHTODRILL]  = $pathtodfile" >>$path/Settings.txt
			echo "[HIGHT] = "
				read hight
			echo "[HIGHT] = $hight mm">>$path/Settings.txt
			echo "[SPEED] = "
				read speed
			echo "[SPEED] = $speed mm/sec">>$path/Settings.txt
		 ;;
		###################################################
	 -m)./Release/MaskMaking ~/thec/gerber/content/MFP/MFP-B_Mask.gbr 18 ;;
	--mask)./Release/MaskMaking ~/thec/gerber/content/MFP/MFP-B_Mask.gbr 18 ;;
	-h) echo " -d or --drill"
		echo " -c or --cut"
 		echo " -s or --settings"
		echo " -m or --mask"
 		echo " -g or --grave"
		echo " -t or --test"
 		echo " -h or --help"
 ;;
	--help) 
		echo " -d or --drill"
		echo " -c or --cut"
 		echo " -p or --settings"
		echo " -m or --mask"
 		echo " -g or --grave"
		echo " -t or --test"
 		echo " -h or --help"
 ;;
	*)echo " *[Don't know parametr]" ;;
esac
shift
done

