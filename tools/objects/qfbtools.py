########################################################################################
# Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               #
#                                                                                      #
# This program is free software; you can redistribute it and/or modify it under        #
# the terms of the GNU General Public License as published by the Free Software        #
# Foundation; either version 3 of the License, or (at your option) any later           #
# version.                                                                             #
#                                                                                      #
# This program is distributed in the hope that it will be useful, but WITHOUT ANY      #
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      #
# PARTICULAR PURPOSE. See the GNU General Public License for more details.             #
#                                                                                      #
# You should have received a copy of the GNU General Public License along with         #
# this program.  If not, see <http://www.gnu.org/licenses/>.                           #
########################################################################################
#
# This library provides some tools for formatting
# parameters name.

def lowerCamelCase(name):
    if len(name) == 0:
        return name
    return name[0].lower() + name[1:]

def isPointer(name):
    if len(name) == 0:
        return False

    if name.strip()[-1:] == "*":
        return True
    else:
        return False

def split(name):
    return name.split("_")

def camelCase(splitted):
    newSplitted = []
    for splittedWord in splitted:
        splittedWord = splittedWord.lower()
        splittedWord = splittedWord[0].upper() + splittedWord[1:]
        newSplitted.append(splittedWord)
    camelCase = "".join(newSplitted)
    camelCase = camelCase[0].lower() + camelCase[1:]
    return camelCase

def staticKey(splitted, className):
    newSplitted = []
    newSplitted.append(className.upper())
    for splittedWord in splitted:
        newSplitted.append(splittedWord.upper())
    newSplitted.append("KEY")
    staticKey = "_".join(newSplitted)
    return staticKey
