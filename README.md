# btrbk-gui

## Introduction

This is a simple GUI for btrbk showing an icon (to be precise: an app-indicator) that indicates the state of the backup:

* successful:  ![successful](/doc/backup-ok.jpg)
* running:     ![successful](/doc/backup-running.jpg)
* error:       ![successful](/doc/backup-err.jpg)

An optional window shows the date and time of the last successful 
backup and the log file of btrbk. It is written for Gnome using GTK and I've tested it on Ubuntu 20.04.

![Screenshot](/doc/screenshot.jpg)

## Motivation

My intention for writing this small tool is my experience with Time Machine for macOS. Btrfs and btrbk are great for backups but I missed a simple icon giving me some feedback about the state. I'm not sure if I will extend this tool in future with a lot of other features as this is more or less all I want. 

Furthermore, I prefer old-school autotools and C++ so I use this for this tool.

## Compile and Install

First install everything we need for compilation:

```
sudo apt install automake autoconf g++ make libgtkmm-3.0-dev libappindicator3-dev
```

Now generate files and compile:

```
aclocal && autoconf && automake --add-missing --foreign && ./configure && make
```

And install with:

```
sudo make install
```

Note that the executable will not work without installation as it searches for icons etc. in the installation destination.

## Usage

A log file written by btrbk is required so that this tool can read it. I assume the log file is `/var/log/btrbk.log`. Probably your btrbk must be configured to write this log here. You may give another path as a parameter like `btrbk-gui /var/log/other-btrbk.log`.
