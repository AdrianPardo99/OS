#!/usr/bin/env bash
##Creado por Adrian González Pardo & Melani Betsabee Valdez Esquivel
##Fecha de modificaciótam: 10/04/2019
##Correo electronico:gozapaadr@gmail.com & betsabi100198@gmail.com*/
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
