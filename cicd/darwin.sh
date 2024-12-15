#!/usr/bin/env sh 

if [ -z "$1" ]; then
	echo "No operation specified!"
	exit 1
fi

case "$1" in
	'docs'|'pack')
		brewdeps+=" doxygen graphviz mactex-no-gui"
		;;
esac

# installing homebrew 
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# installing dependencies
brew install cmake git $brewdeps

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
export REPO="$SCRIPT_DIR/.."

cmake -P "$SCRIPT_DIR/cmake/$1.cmake"
