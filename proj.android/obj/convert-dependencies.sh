#!/bin/sh
# AUTO-GENERATED FILE, DO NOT EDIT!
if [ -f $1.org ]; then
  sed -e 's!^E:/Tool/cygwin/lib!/usr/lib!ig;s! E:/Tool/cygwin/lib! /usr/lib!ig;s!^E:/Tool/cygwin/bin!/usr/bin!ig;s! E:/Tool/cygwin/bin! /usr/bin!ig;s!^E:/Tool/cygwin/!/!ig;s! E:/Tool/cygwin/! /!ig;s!^K:!/cygdrive/k!ig;s! K:! /cygdrive/k!ig;s!^I:!/cygdrive/i!ig;s! I:! /cygdrive/i!ig;s!^G:!/cygdrive/g!ig;s! G:! /cygdrive/g!ig;s!^E:!/cygdrive/e!ig;s! E:! /cygdrive/e!ig;s!^D:!/cygdrive/d!ig;s! D:! /cygdrive/d!ig;s!^C:!/cygdrive/c!ig;s! C:! /cygdrive/c!ig;' $1.org > $1 && rm -f $1.org
fi
