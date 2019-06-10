#!/bin/bash
gnome-terminal -x bash -c "cd Server; node server.js; exec $SHELL"
gnome-terminal -x bash -c "cd src; yarn start; exec $SHELL"
