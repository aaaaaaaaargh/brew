##
#
#  |_  _ _
#  |_)| (/_VV
#
#  Copyright 2015-2018 Marcus v. Keil
#
##

cmake_minimum_required(VERSION 3.6)

brew_add_test(Buffer buffer.cpp)

brew_add_test(ProxyManager proxymanager.cpp)

brew_add_test(SystemInfo systeminfo.cpp)

brew_add_test(Tree tree.cpp)