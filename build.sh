#!/bin/bash

set -e

if [[ ! -d build ]]; then
	mkdir -p Build
fi

pushd Build
	cmake ../
	make
popd

echo -e "\nDone!"
