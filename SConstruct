# -*- coding: utf8 -*-
"""
    author: Steve Göring
    contact: stg7@gmx.de
    2018
"""
"""
    This file is part of cloom.

    cloom is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cloom is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cloom.  If not, see <http://www.gnu.org/licenses/>.
"""
import os
import sys
import glob
import multiprocessing

SetOption('num_jobs', multiprocessing.cpu_count()) # build with all aviable cpu cores/threads


env = Environment(CPPPATH = ['/', "src/"],
                  LIBS = [""], LIBPATH = ['.'],
                  )



env.Decider('MD5')

conf = Configure(env)
libs = ["pthread"]
for l in libs:
    if not conf.CheckLib(l, language="c++"):
        print "Unable to find lib: " + l + ". Exiting."
        sys.exit(-1)


env.Append(CXXFLAGS=['-std=c++14'])

# if you call scons debug=1 debug build is activated
if ARGUMENTS.get('debug', 0) != 0:
    # more checks
    env.Append(CXXFLAGS=['-Wall','-pedantic-errors'])
    # "no" optimization
    env.Append(CCFLAGS=['-O0'])
else:
    env.Append(CXXFLAGS=['-march=native']) # use native architecture
    env.Append(CCFLAGS=['-O3']) # 03

    # loop unrolling and link time optimization, options should be tested
    #env.Append(CCFLAGS=['-funroll-loops', '-flto', '-fwhole-program'])

sources = ["main.cpp"]

env.Program('cloom', sources)



