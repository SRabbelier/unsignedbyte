files=`find . -name "*.cpp" -or -name "*.h"`

##
## fix workspace
##
for file in $files
do
#	echo fixing file $file ...
	## replace any windows crlf with unix lf
	\rm  -f $file.tmp
	sed 's_\r__g' $file > $file.tmp
#	sed 's_sverre@rabbelier.nl_Sverre@Rabbelier.nl_g' $file.tmp > $file.tmp
	mv $file.tmp $file
done

