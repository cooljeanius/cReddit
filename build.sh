#!/bin/sh

set -ex

# flag-dedup and flag-sort did not seem to be working so I removed them

gcc -g -O2 -I/opt/local/include -DHAVE_CONFIG_H -Wall -o cReddit main.c reddit.c jsmn.c -lncursesw -L/opt/local/lib -lcurl -lcares -lidn -lssh2 -lssh2 -lssl -lcrypto -lssl -lcrypto -llber -lldap -lz 

# I originally used "@AM_CFLAGS@" instead of "-Wall" but that didn't get replaced properly...
