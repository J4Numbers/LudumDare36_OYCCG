#!/bin/bash

function toucher()
{
    echo "Creating file $1.$2 in the $MAINPROJ project...";
    touch $MAINPROJ/$SUBPROJ/$3/$1.$2;
    echo "File has been created.";
}

function showHelp()
{
    echo "To use this command, please append any of the following flags:";
    echo "    -c : Create a new pair of files in the $MAINPROJ project";
    echo "    -s : Create a new .cpp file in the $MAINPROJ project";
    echo "    -n : Create a new .hpp file in the $MAINPROJ project";
    echo "    -h : See this help screen";
}

function create() 
{
    if [[ $1 == "-s" ]] || [[ $1 == "-c" ]]; then
        toucher "$2" "cpp" "src";
        valid=1;
    fi
    if [[ $1 == "-n" ]] || [[ $1 == "-c" ]]; then
        toucher "$2" "hpp" "headers";
        valid=1;
    fi
    if [[ $valid != 1 ]]; then
        showHelp;
    fi
}

MAINPROJ="OnlyYouCanCommitGenocide";
SUBPROJ="Only\ You\ Can\ Commit\ Genocide";

if [[ $1 == "-h" ]]; then
    showHelp;
else
    create $1 $2;
fi

