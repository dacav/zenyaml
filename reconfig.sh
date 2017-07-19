#!/bin/sh

set -xe

libtoolize
aclocal
autoheader
autoconf
automake --add-missing
