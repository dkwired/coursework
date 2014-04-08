#!/bin/bash

# Name: David Klein
# Login: kleind
# Class: CS 183
# Lab: Lab 1
# File: chkconfig.sh

chkconfig --level 3 gpm off # handles cut and paste for virtual consoles
chkconfig --level 3 haldaemon on # maintains a list of devices contected to the system
chkconfig --level 3 iscsi off # export and arbitrary number of block devices via TCP/IP
chkconfig --level 3 iscsid off # used after startup to get iscsi devices
chkconfig --level 3 kudzu on # dectects and configures new or change hardware on a system, only runs at boot time
chkconfig --level 3 lvm2-monitor off # linux volume manager
chkconfig --level 3 mcstrans off # daemon translation security context information, SELINUX disabled
chkconfig --level 3 messagebus off # broadcasts notifications of system events
chkconfig --level 3 netfs off # API to interface with network configurations
chkconfig --level 3 network on # handles network interface
chkconfig --level 3 rawdevices off # used to bind a linux raw character device to a block device
chkconfig --level 3 restorecond off # maintains correct file context associate with policy SELINUX disabled
chkconfig --level 3 sshd off # not going to be using SSH
chkconfig --level 3 syslog off # records system events to log files

# multipathd off checks for failed paths and monitors them
# netconsole off logs kernel printk messages over UDP allowing debugging
# netplugd off responds to network link events from linux kernel
# rdisc off implements client side of the ICMP router discover protocol, populate network routing tables
# tcsd off manages TPM and handles requesst from TSP's both local and remote

exit 0
