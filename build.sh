#!/bin/sh

set -ex

# flag-dedup and flag-sort did not seem to be working so I removed them

/usr/local/bin/gcc -g3 -Og -I/opt/local/include -DHAVE_CONFIG_H -Wall -Wextra -pedantic -Wnull-dereference -Warray-bounds=2 -o cReddit main.c reddit.c jsmn.c -L/opt/local/lib -lncurses -L/opt/local/lib -lcurl -lcares -lidn2 -lssh2 -lssh2 -lpsl -lssl -lcrypto -lssl -lcrypto -lldap -llber -lz 

# I originally used "@AM_CFLAGS@" instead of "-Wall" but that didn't get replaced properly...
