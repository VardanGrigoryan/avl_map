##################################
#  The build script is intended  # 
#  to build the test project.    #
##################################

Usage()
{
	echo "Usage: $0 -a <arch> -o <os> -l <limit>
	      Example: $0 -a x64 -o unix -l 100 -c y
	      Where:
	             -a - Architecture [64/x86].
		     -o - Operating system [unix/win].
		     -t - Build type [debug/release].
		     -l - Number of iterations [any integer number].
		     -c - Whether to clean the project [y/n].
	     "
	exit 1
}

# Default assignements for command line arguments.
arg_arc=x64
arg_os=unix
arg_type=debug
arg_limit=100
arg_clean=n

while [ $# -ne 0 ]; do
	case $1 in
		-a)
			arg_arc=$2
			shift 2
			;;
		-o)
			arg_os=$2
			shift 2
			;;
		-t)
			arg_type=$2
			shift 2
			;;
		-l)
			arg_limit=$2
			shift 2
			;;
		-c)
			arg_clean=$2
			shift 2
			;;
		*)
			Usage
	esac
done

arc=''
case $arg_arc in
	x64 ) arc='x64';;
	x86 ) arc='x86';;
	*) echo "Error: Unrecognized argument value: '$arg_arc'."; echo; echo "See usage."; Usage; exit -1;;
esac

os=''
case $arg_os in
	unix ) os='_UNIX_';;
	win ) os='';;
	*) echo "Error: Unrecognized argument value: '$arg_os'."; echo; echo "See usage."; Usage; exit -1;;
esac

type=''
case $arg_type in
	debug ) type='DEBUG';;
	release ) type='RELEASE';;
	*) echo "Error: Unrecognized argument value: '$arg_type'."; echo; echo "See usage."; Usage; exit -1;;
esac

clean=''
case $arg_clean in
	y ) clean=make_clean;;
	n ) clean=;;
	*) echo "Error: Unrecognized argument value: '$arg_clean'.";echo; echo "See usage.";Usage; exit -1;;
esac

build_dir_name=build
build_dir=`pwd`/$build_dir_name
build_sys=cmake
build_tool=make
log_dir_name=test.log
log_file=$build_dir/$log_dir_name

build() {
	echo "Info: CMake starts ..."
	if [ ! -d $build_dir ]; then
		echo "Info: Creating $build_dir"
		mkdir $build_dir
	fi
	cd $build_dir
	$build_sys -G "Unix Makefiles" -DCMAKE_BUILD_TYPE:INTERNAL=$type -DARC=$arc -DOS=$os -D_LIMIT_=$arg_limit .. 2>&1 > log_file
	cmexit_code=${PIPESTATUS[0]}
	if [[ $cmexit_code -ne 0 ]]
	then
		echo "Error: ${build_sys} aborted."
		exit -1
	fi
	$build_tool 2>&1 > log_file
	mexit_code=${PIPESTATUS[0]}
	if [[ $mexit_code -ne 0 ]]
	then
		echo "Error: ${build_tool} aborted."
		exit -1
	fi
	cd ..
	echo "Info: Build done successfully"
}

make_clean() {
	echo "Info: Cleaning."
	if [[ ! -d $build_dir ]]; then
		echo "Warning: Couldn't find $build_dir. Cleaning skiped."
	else
		cd $build_dir
		$build_tool clean
		cd ..
		echo "Info: Cleaning is done successfully."
	fi
}

build
