#!/bin/bash

cp mruby/mrbgems/mruby-bin-mirb/tools/mirb/mirb.c src/mirb.c

sed -i 's/^main(/mirb_main(/' src/mirb.c
sed -i 's/"mruby\/array.h"/<mruby\/array.h>/' src/mirb.c
