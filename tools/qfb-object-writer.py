#!/usr/bin/python
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
# This tool is used to quickly create objects
# that can expose Facebook API through properties.
#
# Note that while the object parser should be able to distinguish date time
# components while parsing, it is not able to distinguish URL or integers
# from strings. Conversions are then done inside the object, that is here

import argparse
import re
import qfbobjectdescriptionfileparser
import qfbtools

copyright = """/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/
"""

knownTypes = {"int": "toString().toInt", "QString": "toString", "QDateTime": "toDateTime",
              "bool": "toBool", "double": "toDouble"}

class ImplementationData:
    includes = ""
    headerCode = ""
    sourceCode = ""
    objectCreationCode = ""
    variablesCode = {}


# Generate files
def generate(input):
    parserData = qfbobjectdescriptionfileparser.parse(input)
    if parserData.className == "" or parserData.baseClass == "":
        print """Error: parsed data is invalid"""
        return
    data = detectImplementation(parserData)
    implementationData = data["implementation"]
    parserData = data["parserData"]
    createHeader(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables, implementationData)
    createSource(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables, implementationData)


def detectImplementation(parserData):
    implementationData = ImplementationData()

    input = parserData.className.lower()
    try:
        headerFile = open(input + ".h")
        foundIncludesMarker = False
        for line in headerFile:
            if line.strip() == "// <<<<< includes":
                foundIncludesMarker = False

            if foundIncludesMarker:
                implementationData.includes += line

            if line.strip() == "// >>>>> includes":
                foundIncludesMarker = True
        headerFile.close()

        headerFile = open(input + ".h")
        foundHeaderMarker = False
        for line in headerFile:
            if line.strip() == "// <<<<< custom header code":
                foundHeaderMarker = False

            if foundHeaderMarker:
                implementationData.headerCode += line

            if line.strip() == "// >>>>> custom header code":
                foundHeaderMarker = True
        headerFile.close()
        print "Header file was found. It will be patched"
    except:
        pass


    try:
        sourceFile = open(input + ".cpp")
        foundSourceMarker = False
        for line in sourceFile:
            if line.strip() == "// <<<<< custom source code":
                foundSourceMarker = False

            if foundSourceMarker:
                implementationData.sourceCode += line

            if line.strip() == "// >>>>> custom source code":
                foundSourceMarker = True
        sourceFile.close()

        sourceFile = open(input + ".cpp")
        foundObjectCreationMarker = False
        for line in sourceFile:
            if line.strip() == "// <<<<< custom object creation code":
                foundObjectCreationMarker = False

            if foundObjectCreationMarker:
                implementationData.objectCreationCode += line

            if line.strip() == "// >>>>> custom object creation code":
                foundObjectCreationMarker = True

        sourceFile.close()
        print "Source file was found. It will be patched"
    except:
        pass

    variableNames = []
    variableTypes = {}
    for variable in parserData.variables:
        if variable["type"] != "NO" and variable["type"] != "TODO":
            variableNames.append(variable["name"])
            if not variable["isList"]:
                variableTypes[variable["name"]] = variable["type"]
            else:
                variableTypes[variable["name"]] = "QList<" + variable["type"] + ">"
    try:
        regExpMatcher = re.compile("([^\\(]+)\\(\\)\\s+const;")
        headerFile = open(input + ".h")
        for line in headerFile:
            result = regExpMatcher.match(line.strip())
            if result != None:
                capturedData = result.group(1)
                splittedCapturedData = capturedData.split(" ")
                name = splittedCapturedData[-1].strip()
                type = " ".join(splittedCapturedData[:-1]).strip()

                if name in variableNames:
                    if type != variableTypes[name]:
                        for variable in parserData.variables:
                            if variable["name"] == name:
                                variable["type"] = type

        headerFile.close()
    except:
        pass

    try:
        sourceFile = open(input + ".cpp")

        foundMarker = False
        propertyName = ""
        for line in sourceFile:
            if foundMarker and line.strip() == "// <<<<< property " + propertyName:
                foundMarker = False
                propertyName = ""

            if foundMarker:
                implementationData.variablesCode[propertyName] += line

            if line.strip().startswith("// >>>>> property"):
                foundMarker = True
                propertyName = line.strip()[17:].strip()
                implementationData.variablesCode[propertyName] = ""


        sourceFile.close()
    except:
        pass


    return {"implementation": implementationData, "parserData": parserData}

def createHeader(className, includes, baseClass, variables, implementationData):
    header = copyright
    header += """
#ifndef QFB_""" + className.upper() + """_H
#define QFB_""" + className.upper() + """_H

/**
 * @file """ + className.lower() + """.h
 * @brief Definition of QFB::""" + className + """
 */

#include \"""" + baseClass.lower() + """.h\"
// >>>>> includes
"""
    if implementationData.includes != "":
        header += implementationData.includes
    else:
        for include in includes:
            if include != "\"" + baseClass.lower() + ".h\"":
                header += "#include " + include + "\n"
    header += """// <<<<< includes

"""
    aOrAn = "a"
    firstLetter = className[0].lower()
    isA = firstLetter == "a"
    isE = firstLetter == "e"
    isI = firstLetter == "i"
    isO = firstLetter == "o"
    isU = firstLetter == "u"
    if isA or isE or isI or isO or isU:
        aOrAn = "an"

    header += """namespace QFB {
class """ + className + """Private;
/**
 * @short """ + aOrAn[0].upper() + aOrAn[1:] + " " + className.lower() + """
 *
 * This class represents """ + aOrAn +  " " + className.lower() +  """ in Facebook.
 * Extending QFB::""" + baseClass +  """, it contains a lot of properties
 * that can be accessed through
"""
    for variable in variables:
        if variable["name"] != "id" and variable["name"] != "name":
            if variable["type"] != "TODO" and variable["type"] != "NO" and not variable["isList"]:
                header += " * - " + qfbtools.camelCase(qfbtools.split(variable["name"])) + "()\n"
    header += """ *
 * Some of these fields might not be set, because of
 * users hiding them in their settings, or because of
 * missing permissions.
 *
 * You can choose the fields you want using the "fields"
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * These parameters should be added to the query that is used
 * to get """ + aOrAn + " " + className.lower() + """.
"""

    missing = []
    for variable in variables:
        if variable["type"] == "TODO":
            missing.append(qfbtools.camelCase(qfbtools.split(variable["name"])))
    if len(missing) > 0:
        header += """ *
 * @section missing Missing properties
 *
 * Some fields such as """
        header += ", ".join(missing)
        header += """
 * are not yet implemented.
"""
    no = []
    for variable in variables:
        if variable["type"] == "NO":
            no.append(qfbtools.camelCase(qfbtools.split(variable["name"])))
    if len(no) > 0:
        header += """ *
 * @section notImplemented Not implemented
 *
 * Fields """
        header += ",".join(no)
        header += """
 * will not be implemented.
"""
    header += """ */
class QFBBASE_EXPORT """ + className + """: public """ + baseClass + """
{
    Q_OBJECT
"""
    for variable in variables:
        if variable["name"] != "id" and variable["name"] != "name":
            if variable["doc"] != "" and not variable["isList"]:
                splittedDoc = variable["doc"].split("\n")
                header += "    /**\n     * @short " + splittedDoc[0] + "\n"
                del splittedDoc[0]
                for docLine in splittedDoc:
                    header += "     * " + docLine + "\n"
                header += "     */\n"
            if variable["type"] == "TODO":
                header += "    /// @todo " + variable["name"] + "\n"
            elif variable["type"] == "NO":
                header += "    // " + variable["name"] + " will not be implemented\n"
            elif variable["type"] != "" and not variable["isList"]:
                header += "    Q_PROPERTY(" + variable["type"] + " "
                header += qfbtools.camelCase(qfbtools.split(variable["name"]))
                header += " READ " + qfbtools.camelCase(qfbtools.split(variable["name"]))
                header += " CONSTANT)\n"

    header += "    // >>>>> custom header code\n"
    if implementationData.headerCode != "":
        header += implementationData.headerCode
    header += """    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit """ + className + """(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit """ + className + """(const QVariantMap propertiesMap, QObject *parent = 0);
"""
    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "NO" and variable["type"] != "":
            if variable["name"] != "id" and variable["name"] != "name":
                splittedName = qfbtools.split(variable["name"])
                readableName = " ".join(splittedName)
                upperReadableName = readableName[0].upper() + readableName[1:]
                header += """    /**
     * @brief """ + upperReadableName + """
     * @return """ + readableName + """.
     */
    """
                if variable["isList"]:
                    header += "QList<" + variable["type"] + "> "
                else:
                    header += variable["type"] + " "
                header += qfbtools.camelCase(splittedName) + "() const;\n"

    header += """private:
    Q_DECLARE_PRIVATE(""" + className + """)
};

}

Q_DECLARE_METATYPE(QFB::""" + className + """ *)


#endif // QFB_""" + className.upper() + """_H
"""

    headerFile = open(className.lower() + ".h", "w")
    headerFile.write(header)
    headerFile.close()

def createSource(className, includes, baseClass, variables, implementationData):
    source = copyright
    source += """
/**
 * @file """ + className.lower() + """.cpp
 * @brief Implementation of QFB::""" + className + """
 */

#include \"""" + className.lower() + """.h\"
#include \"private/helper_p.h\"
#include \"private/objectbase_p.h\"
#include \"private/object_creator_p.h\"

namespace QFB
{

"""

    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "NO" and variable["type"] != "":
            if variable["name"] != "id" and variable["name"] != "name":
                splittedName = qfbtools.split(variable["name"])
                source += """/**
 * @internal
 * @brief """ + qfbtools.staticKey(splittedName, className) + """
 */
static const char *""" + qfbtools.staticKey(splittedName, className) + " = "
                source += "\"" + variable["name"] + "\";\n"


    source += """

/**
 * @internal
 * @short Private class for QFB::""" + className + """
 */
class """ + className + """Private: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit """ + className + """Private();
"""
    for variable in variables:
        if qfbtools.isPointer(variable["type"]) or variable["isList"]:
            splittedName = qfbtools.split(variable["name"])
            readableName = " ".join(splittedName)
            if variable["isList"]:
                readableName = "List of " + readableName
            else:
                readableName = readableName[0].upper() + readableName[1:]
            source += """    /**
     * @internal
     * @short """ + readableName + """
     */
"""
            if not variable["isList"]:
                source += "    " + variable["type"] + " " + qfbtools.camelCase(splittedName) + ";\n"
            else:
                source += "    QList<" + variable["type"] + "> " + qfbtools.camelCase(splittedName)
                source += ";\n"
    source += """};

""" + className + "Private::" + className + """Private():
    ObjectBasePrivate()
{
}

////// End of private class //////

"""

    source += className + "::" + className + """(QObject *parent):
    """ + baseClass + """(parent)
{
}

"""

    source += className + "::" + className
    source += """(const QVariantMap propertiesMap, QObject *parent):
    """ + baseClass + """(*(new """ +  className + """Private), parent)
{
    Q_D(""" + className + """);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
"""
    if implementationData.objectCreationCode != "":
        source += implementationData.objectCreationCode
    else:
        source += """    // TODO: check object creation
    // It was done automatically by a script
"""

        for variable in variables:
            if qfbtools.isPointer(variable["type"]) or variable["isList"]:
                splittedName = qfbtools.split(variable["name"])
                source += "    // Create " + qfbtools.camelCase(splittedName) + "\n"
                if not variable["isList"]:
                    source += "    QVariantMap " + qfbtools.camelCase(splittedName) + "Data = "
                    source += "d->propertiesMap.take("
                    source += qfbtools.staticKey(splittedName, className) + ")."
                    source += "toMap();\n"
                    source += "    d->" + qfbtools.camelCase(splittedName) + " = createObject<"
                    source += variable["type"][:-1].strip()
                    source += ">(" + qfbtools.camelCase(splittedName)
                    source += "Data, this);\n"
                else:
                    source += "    QVariantList " + qfbtools.camelCase(splittedName) + "Data = "
                    source += "d->propertiesMap.take("
                    source += qfbtools.staticKey(splittedName, className) + ")."
                    source += "toList();\n"
                    source += "    d->" + qfbtools.camelCase(splittedName) + " = "
                    if variable["type"].strip() == "QString":
                        source += "createStringList"
                    else:
                        source += "createList<"
                        source += variable["type"][:-1].strip() + ">"
                    source += "(" + qfbtools.camelCase(splittedName) + "Data"
                    if variable["type"].strip() == "QString":
                        source += ");\n"
                    else:
                        source += ", this);\n"


    source += """    // <<<<< custom object creation code
}

"""
    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "NO" and variable["type"] != "":
            splittedName = qfbtools.split(variable["name"])
            if variable["name"] in implementationData.variablesCode:
                source += variable["type"] + " "
                source +=  className + "::" + qfbtools.camelCase(splittedName) + """() const
{
    Q_D(const """ + className + """);
    // >>>>> property """ + variable["name"] + """
"""
                source += implementationData.variablesCode[variable["name"]]
                source += """    // <<<<< property """ + variable["name"] + """
}

"""

            elif variable["name"] != "id" and variable["name"] != "name":
                if variable["isList"]:
                    source += "QList<" + variable["type"] + "> "
                else:
                    source += variable["type"] + " "
                source +=  className + "::" + qfbtools.camelCase(splittedName) + """() const
{
    Q_D(const """ + className + """);
    // >>>>> property """ + variable["name"] + """
"""
                if variable["isList"]:
                    source += "    return d->" + qfbtools.camelCase(splittedName) + ";\n"
                else:
                    if variable["type"] in knownTypes:
                        source += "    return d->propertiesMap.value("
                        source += qfbtools.staticKey(splittedName, className)
                        source += ")." + knownTypes[variable["type"]] + "();\n"
                    elif variable["type"] == "QUrl":
                        source += "    return parseUrl(d->propertiesMap.value("
                        source += qfbtools.staticKey(splittedName, className)
                        source += ").toString());\n"
                    elif qfbtools.isPointer(variable["type"]):
                        source += "    return d->" + qfbtools.camelCase(splittedName) + ";\n"
                    else:
                        source += "    // TODO: define the returned data\n"
                source += """    // <<<<< property """ + variable["name"] + """
}

"""

    source += """
// >>>>> custom source code
"""

    source += implementationData.sourceCode

    source += """// <<<<< custom source code

}
"""

    sourceFile = open(className.lower() + ".cpp", "w")
    sourceFile.write(source)
    sourceFile.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='QFB object writer')
    parser.add_argument('input', metavar='input', type=str,
                        help="""Input file""")
    args = parser.parse_args()
    input = args.input
    generate(input)