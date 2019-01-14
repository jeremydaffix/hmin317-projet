#!/bin/sh


if [ "$#" -ne 2 ]; then
    echo "USAGE: generate-component MyComponentClass myComponentFileName"
    exit 1
fi

# arguments
CLASSNAME=$1
CLASSNAMEH=${1^^}
FILENAME=$2


# lecture des fichiers de models

CPP=""
while read line; do    
    CPP="$CPP\n$line"
done < component.cpp.model

HPP=""
while read line; do    
    HPP="$HPP\n$line"
done < component.hpp.model


# on remplace les variables dans les models

CPP="${CPP//###CLASSNAME###/$CLASSNAME}"
CPP="${CPP//###CLASSNAMEH###/$CLASSNAMEH}"
CPP="${CPP//###FILENAME###/$FILENAME}"

HPP="${HPP//###CLASSNAME###/$CLASSNAME}"
HPP="${HPP//###CLASSNAMEH###/$CLASSNAMEH}"
HPP="${HPP//###FILENAME###/$FILENAME}"



# generation des fichiers

echo -ne "$CPP" > $FILENAME.cpp
echo "$FILENAME.cpp GENERATED"

echo -ne "$HPP" > $FILENAME.h
echo "$FILENAME.h GENERATED"

mv $FILENAME.cpp ../src/game/
mv $FILENAME.h ../src/game/


