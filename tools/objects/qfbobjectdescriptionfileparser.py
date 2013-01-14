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
# This library provides capabilities to parse files that describes a Facebook object, and
# translate it into an organized data.
#
# Files describing Facebook data takes the following form.
#
# MyFacebookObject
# "firstinclude.h"
# <another/include>
# ---
# First line of documentation (@short)
#
# Another line
# Yet another line
# QString property1
# ---
# Documentation
# int another_property
# ---
# Another documentation
# Object * composite_property
# ---
# todo_entries_should_not_have_doc_and_type
# ---
# <no> not_implemented_entries_are_like_todo_but_with_the_prefix
# More description
# <list> DataStructure * list_of_properties

import qfbtools

class ParserData:
    className = ""
    bassClass = ""
    haveSubObjects = False
    includes = []
    variables = []

def _createGroup(groupData):
    splittedGroupData = groupData.strip().split("\n")
    group = {}
    group["doc"] = ""
    group["isList"] = False
    group["type"] = ""
    group["name"] = ""

    # Check if it is a todo
    if len(splittedGroupData) == 1:
        splittedTodoName = splittedGroupData[0].strip().split(" ")
        if len(splittedTodoName) == 1:
            group["name"] = splittedTodoName[0]
            if group["name"] != "":
                group["type"] = "TODO"
        if len(splittedTodoName) == 2:
            if splittedTodoName[0] == "<no>":
                group["name"] = splittedTodoName[1]
                if group["name"] != "":
                    group["type"] = "NO"
        return group


    # Extract the line containing name and type
    isList = False
    nameAndType = splittedGroupData[-1]
    splittedGroupData = splittedGroupData[:-1]
    splittedNameAndType = nameAndType.split(" ")
    if splittedNameAndType[0].strip() == "<list>":
        isList = True
        del splittedNameAndType[0]

    group["name"] = splittedNameAndType[-1].strip()
    splittedNameAndType = splittedNameAndType[:-1]
    group["type"] = " ".join(splittedNameAndType).strip()
    group["doc"] = "\n".join(splittedGroupData).strip()
    group["isList"] = isList
    return group

def parse(fileName):
    parserData = ParserData()

    # Open the file and get data
    f = open(fileName)
    data = ""
    for line in f:
        data += line

    splittedData = data.strip().split("---")

    if len(splittedData) < 2:
        print """Error: the file is malformatted.
The main groups are missing."""
        return parserData

    # Parse the first group (class name and includes)
    firstGroup = splittedData[0]
    del splittedData[0]

    splittedFirstGroup = firstGroup.strip().split("\n")
    if len(splittedFirstGroup) == 0:
        print """Error: the file is malformatted
The first group should have at least the name of the class"""
        return parserData

    # The class name is the first line
    parserData.className = splittedFirstGroup[0]
    del splittedFirstGroup[0]

    # The other lines are headers
    for splittedFirstGroupItem in splittedFirstGroup:
        strippedSplittedItem = splittedFirstGroupItem.strip()
        if strippedSplittedItem != "":
            parserData.includes.append(strippedSplittedItem)

    # Parse the variables
    for groupData in splittedData:
        group = _createGroup(groupData)
        if group["name"] != "" and group["type"] != "":
            parserData.variables.append(group)

    # Find the parent class
    parserData.baseClass = "ObjectBase"
    haveId = False
    haveName = False
    for variable in parserData.variables:
        if variable["name"] == "id" and variable["type"] == "QString":
            haveId = True
        if variable["name"] == "name" and variable["type"] == "QString":
            haveName = True

    if haveId and haveName:
        parserData.baseClass = "NamedObject"
    elif haveId:
        parserData.baseClass = "Object"

    # Find if there are sub-objects
    for variable in parserData.variables:
        if qfbtools.isPointer(variable["type"]):
            parserData.haveSubObjects = True
    return parserData