#!/bin/bash

#script to init system state to run garden control system

gksu su

#install dev Env

apt-get install mysql-server mysql-client mysql-common libqwt5-qt4-dev libqt4-sql-mysql libboost1.40-all-dev dia 

# install user Env

apt-get install mysql-server mysql-client mysql-common libqwt5-qt4 libqt4-sql-mysql 


# install software
apt-get install motion 

#configure software

# setup firewall script
# setup startup
# exit
