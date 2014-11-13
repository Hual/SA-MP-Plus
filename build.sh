#!/bin/bash

set -e

if [[ ! -d Build ]]; then
	mkdir -p Build
fi

pushd Build
	cmake ../
	make
popd

echo -e "\nLinux server binary built!"
