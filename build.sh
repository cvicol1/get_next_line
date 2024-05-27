#!/bin/sh

set 	-xe  #to see the clang line, what am i running

cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000000 *.c