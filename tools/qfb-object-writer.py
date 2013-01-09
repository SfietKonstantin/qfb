#!/usr/bin/python
#
# This tool is used to quickly create objects
# that can expose Facebook API through properties.
#
# You have to provide the properties to expose
# in a separate file. This file describes the name of
# the class, as well as the type and name of the
# properties, that are declared in Facebook API
# documentation.
#
# This tool will automatically convert the properties
# to a camel-case one, and will also export a private
# header with the keys that are used internally.
#
# Example of description file
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

import argparse
import string
import re
import qfbparser
import qfbtools

copyright = """/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

knownTypes = {"int": "toInt", "QString": "toString", "QDateTime": "toDateTime", "QUrl": "toUrl"}

def generate(input):
    parserData = qfbparser.parse(input)

    createHeader(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables)
    createSource(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables)
    createKeys(parserData.className, parserData.includes, parserData.baseClass,
               parserData.variables)

def createHeader(className, includes, baseClass, variables):
    header = copyright
    header += "\n"
    header += "#ifndef QFB_" + className.upper() + "_H\n"
    header += "#define QFB_" + className.upper() + "_H\n\n"
    header += "/**\n"
    header += " * @file " + className.lower() + ".h\n"
    header += " * @brief Definition of QFB::" + className + "\n"
    header += " */\n\n"
    header += "#include \"" + baseClass.lower() + ".h\"\n"
    for include in includes:
        if include != "\"" + baseClass.lower() + ".h\"":
            header += "#include " + include + "\n"

    header += "\nnamespace QFB\n{\n\n"
    header += "/**\n"
    header += " * @short WRITE DOCUMENTATION HERE\n"
    header += " */\n"
    header += "class QFBBASE_EXPORT " + className + ": public " + baseClass + "\n{\n"
    header += "    Q_OBJECT\n"
    for variable in variables:
        if variable["doc"] != "":
            splittedDoc = variable["doc"].split("\n")
            header += "    /**\n"
            header += "     * @short " + splittedDoc[0] + "\n"
            del splittedDoc[0]
            for docLine in splittedDoc:
                header += "     * " + docLine + "\n"
            header += "     */\n"
        if variable["type"] == "TODO":
            header += "    /// @todo " + variable["name"] + "\n"
        elif variable["type"] != "":
            header += "    Q_PROPERTY(" + variable["type"] + " "
            header += qfbtools.camelCase(qfbtools.split(variable["name"]))
            header += " READ " + qfbtools.camelCase(qfbtools.split(variable["name"]))
            header += " CONSTANT)\n"
    header += "public:\n"
    header += "    /**\n"
    header += "     * @brief Invalid constructor\n"
    header += "     * @param parent parent object.\n"
    header += "     */\n"
    header += "    explicit " + className + "(QObject *parent = 0);\n"
    header += "    /**\n"
    header += "     * @brief Default constructor\n"
    header += "     * @param propertiesMap properties.\n"
    header += "     * @param parent parent object.\n"
    header += "     */\n"
    header += "    explicit " + className + "(const PropertiesMap propertiesMap, "
    header += "QObject *parent = 0);\n"
    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "":
            splittedName = qfbtools.split(variable["name"])
            readableName = " ".join(splittedName)
            upperReadableName = readableName[0].upper() + readableName[1:]
            header += "    /**\n"
            header += "     * @brief " + upperReadableName + "\n"
            header += "     * @return " + readableName + ".\n"
            header += "     */\n"
            header += "    " + variable["type"] + " " + qfbtools.camelCase(splittedName)
            header += "() const;\n"

    header += "private:\n"
    header += "    Q_DECLARE_PRIVATE(ObjectBase)\n"
    header += "};\n\n"
    header += "}\n\n"
    header += "Q_DECLARE_METATYPE(QFB::" + className + " *)\n\n"
    header += "#endif // QFB_" + className.upper() + "_H\n"

    headerFile = open(className.lower() + ".h", "w")
    headerFile.write(header)
    headerFile.close()

def createSource(className, includes, baseClass, variables):
    source = copyright
    source += "\n"
    source += "/**\n"
    source += " * @file " + className.lower() + ".cpp\n"
    source += " * @brief Implementation of QFB::" + className + "\n"
    source += " */\n\n"
    source += "#include \"" + className.lower() + ".h\"\n"
    source += "#include \"objectbase_p.h\"\n"
    source += "#include \"" + className.lower() + "_keys_p.h\"\n\n"
    if baseClass == "NamedObject" :
        source += "#include \"namedobject_keys_p.h\"\n\n"
    if baseClass == "Object" or baseClass == "NamedObject" :
        source += "#include \"object_keys_p.h\"\n\n"

    source += "namespace QFB\n"
    source += "{\n\n"

    source += className + "::" + className + "(QObject *parent):\n"
    source += "    " + baseClass + "(parent)\n"
    source +=  "{\n}\n\n"

    source += className + "::" + className
    source += "(const PropertiesMap propertiesMap, QObject *parent):\n"
    source += "    " + baseClass + "(propertiesMap, parent)\n"
    source += "{\n"
    source += "    Q_D(ObjectBase);\n\n"
    source += "    // TODO: check reparenting\n"
    source += "    // It was done automatically by a script\n\n"
    for variable in variables:
        if qfbtools.isPointer(variable["type"]):
            splittedName = qfbtools.split(variable["name"])
            source += "    // Reparent " + qfbtools.camelCase(splittedName) + "\n"
            source += "    QObject *" + qfbtools.camelCase(splittedName) + "Object = "
            source += "d->propertiesMap.value(" + qfbtools.staticKey(splittedName, className) + ")"
            source += ".value<" + variable["type"] + ">();\n"
            source += "    if (" + qfbtools.camelCase(splittedName) + "Object) {\n"
            source += "        " + qfbtools.camelCase(splittedName) + "Object->setParent(this);\n"
            source += "    }\n\n"

    source += "}\n"

    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "":
            splittedName = qfbtools.split(variable["name"])
            source += variable["type"] + " " + className + "::" + qfbtools.camelCase(splittedName)
            source += "() const\n"
            source += "{\n"
            source += "    Q_D(const ObjectBase);\n"
            source += "    return d->propertiesMap.value("
            key = qfbtools.staticKey(splittedName, className)
            if variable["name"] == "id":
                key = "OBJECT_ID_KEY"
            elif variable["name"] == "name":
                key = "NAMEDOBJECT_NAME_KEY"
            source += key
            source += ")."
            if variable["type"] in knownTypes:
                source += knownTypes[variable["type"]] + "()"
            else:
                source += "value<" + variable["type"] + ">()"
            source += ";\n"
            source += "}\n\n"

    source += "}\n"


    sourceFile = open(className.lower() + ".cpp", "w")
    sourceFile.write(source)
    sourceFile.close()

def createKeys(className, includes, baseClass, variables):
    keys = copyright
    keys += "\n"
    keys += "#ifndef QFB_" + className.upper() + "KEYS_P_H\n"
    keys += "#define QFB_" + className.upper() + "KEYS_P_H\n\n"

    keys += "// Warning\n"
    keys += "//\n"
    keys += "// This file exists for the convenience\n"
    keys += "// of other qfb classes.\n"
    keys += "// This header file may change from version\n"
    keys += "// to version without notice or even be removed.\n\n"

    keys += "/**\n"
    keys += " * @internal\n"
    keys += " * @file " + className.lower() + "_keys_p.h\n"
    keys += " * @brief Definition of internal keys associated to QFB::" + className + "\n"
    keys += " */\n\n"

    keys += "namespace QFB\n"
    keys += "{\n\n"

    for variable in variables:
        if variable["type"] != "TODO" and variable["type"] != "":
            if variable["name"] != "id" and variable["name"] != "name":
                splittedName = qfbtools.split(variable["name"])
                keys += "/**\n"
                keys += " * @internal\n"
                keys += " * @brief " + qfbtools.staticKey(splittedName, className) + "\n"
                keys += " */\n"
                keys += "static const char *" + qfbtools.staticKey(splittedName, className) + " = "
                keys +="\"" + variable["name"] + "\";\n"

    keys += "\n}\n\n"

    keys += "#endif // QFB_" + className.upper() + "KEYS_P_H\n"


    keysFile = open(className.lower() + "_keys_p.h", "w")
    keysFile.write(keys)
    keysFile.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='QFB object writer')
    parser.add_argument('input', metavar='input', type=str,
                        help="""Input file""")
    args = parser.parse_args()

    input = args.input
    generate(input)


