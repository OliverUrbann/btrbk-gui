#!/bin/sh

case "$1" in
    run)
        gnome-terminal -- sh -c 'cd /tmp ; pkexec btrbk run; bash'       
    ;;
    resume)
        gnome-terminal -- sh -c 'cd /tmp ; pkexec btrbk resume; bash'
    ;;
    clean)
        gnome-terminal -- sh -c 'cd /tmp ; pkexec btrbk clean; bash'
    ;;
    kill)
        gnome-terminal -- sh -c 'cd /tmp ; pkexec kill $2; bash'
    ;;
esac
