#!/usr/bin/env bash
if [ "$1" = "" ]
then
  echo "Por favor usa un parametro para trabajar"
  exit
fi

var=$1

onCreate(){
  file=$1
  binary=$(basename $file .c)
  echo "Archivo: ${file}"
  echo "Binario: ${binary}"
  gcc $file -o $binary -pthread
}

onCreate $var
