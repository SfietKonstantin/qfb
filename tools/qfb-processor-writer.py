#!/usr/bin/python
#
# This tool is used to quickly create processors
# that are used to create objects that contain
# information about Facebook.
#
# You have to provide the properties to expose
# in a separate file. This file describes the name of
# the class, as well as the type and name of the
# properties, that are declared in Facebook API
# documentation.
#
# Please look at qfb-object-writer.py for the syntax
# of that file.

import argparse
import string
import re
import qfbtools
import qfbparser

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

def lowerCamelCase(name):
    return name[0].lower() + name[1:]


def generate(input, templateOnly):
    parserData = qfbparser.parse(input)

    createHeader(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables)
    if not templateOnly:
        createHeaderPrivate(parserData.className, parserData.includes, parserData.baseClass,
                            parserData.variables)
    createSource(parserData.className, parserData.includes, parserData.baseClass,
                 parserData.variables, templateOnly)

def createHeader(className, includes, baseClass, variables):
    header = copyright
    header += "\n"
    header += "#ifndef QFB_" + className.upper() + "PROCESSOR_H\n"
    header += "#define QFB_" + className.upper() + "PROCESSOR_H\n\n"
    header += "/**\n"
    header += " * @file " + className.lower() + "processor.h\n"
    header += " * @brief Definition of QFB::" + className + "Processor\n"
    header += " */\n\n"
    header += "#include \"abstractgraphprocessor.h\"\n"

    header += "\nnamespace QFB\n{\n\n"
    header += "class " + className + ";\n"
    header += "class " + className + "ProcessorPrivate;\n"
    header += "/**\n"
    header += " * @short WRITE DOCUMENTATION HERE\n"
    header += " */\n"
    header += "class QFBBASE_EXPORT " + className + "Processor: public AbstractGraphProcessor\n{\n"
    header += "    Q_OBJECT\n"
    header += "public:\n"
    header += "    /**\n"
    header += "     * @brief Default constructor\n"
    header += "     * @param parent parent object.\n"
    header += "     */\n"
    header += "    explicit " + className + "Processor(QObject *parent = 0);\n"
    header += "    /**\n"
    header += "     * @brief " + className + "\n"
    header += "     * @return " + className.lower() + ".\n"
    header += "     */\n"
    header += "    " + className + " * " + lowerCamelCase(className) + "() const;\n"
    header += "protected:\n"
    header += "    bool processDataSource(QIODevice *dataSource);\n"
    header += "private:\n"
    header += "    Q_DECLARE_PRIVATE(" + className + "Processor)\n"
    header += "};\n\n"
    header += "}\n\n"
    header += "#endif // QFB_" + className.upper() + "PROCESSOR_H\n"

    headerFile = open(className.lower() + "processor.h", "w")
    headerFile.write(header)
    headerFile.close()

def createPrivateClass(className, templateOnly):
    privateClass = "class " + className + ";\n"
    privateClass += "/**\n"
    privateClass += " * @internal\n"
    privateClass += " * @brief Private class for QFB::" + className +"Processor\n"
    privateClass += " */\n"
    privateClass += "class " + className + "ProcessorPrivate: "
    privateClass += "public AbstractGraphProcessorPrivate\n{\n"
    privateClass += "public:\n"
    privateClass += "    /**\n"
    privateClass += "     * @internal\n"
    privateClass += "     * @brief Default constructor\n"
    privateClass += "     */\n"
    privateClass += "    explicit " + className + "ProcessorPrivate();\n"
    if not templateOnly:
        privateClass += "    /**\n"
        privateClass += "     * @internal\n"
        privateClass += "     * @brief Create a " + className + "\n"
        privateClass += "     * @param jsonObject JSON object used to create the "
        privateClass += className + ".\n"
        privateClass += "     * @return created " + className + ".\n"
        privateClass += "     */\n"
        privateClass += "    static " + className + " * create" + className
        privateClass += "(const JsonObject &jsonObject);\n"
    privateClass += "    /**\n"
    privateClass += "     * @internal\n"
    privateClass += "     * @brief " + className + "\n"
    privateClass += "     */\n"
    privateClass += "    " + className + " * " + lowerCamelCase(className) + ";\n"
    privateClass += "};\n\n"
    return privateClass

def createHeaderPrivate(className, includes, baseClass, variables):

    headerPrivate = copyright
    headerPrivate += "\n"
    headerPrivate += "#ifndef QFB_" + className.upper() + "PROCESSOR_P_H\n"
    headerPrivate += "#define QFB_" + className.upper() + "PROCESSOR_P_H\n\n"

    headerPrivate += "// Warning\n"
    headerPrivate += "//\n"
    headerPrivate += "// This file exists for the convenience\n"
    headerPrivate += "// of other qfb classes.\n"
    headerPrivate += "// This header file may change from version\n"
    headerPrivate += "// to version without notice or even be removed.\n\n"

    headerPrivate += "/**\n"
    headerPrivate += " * @internal\n"
    headerPrivate += " * @file " + className.lower() + "processor_p.h\n"
    headerPrivate += " * @brief Definition of QFB::" + className + "ProcessorPrivate\n"
    headerPrivate += " */\n\n"

    headerPrivate += "#include \"abstractgraphprocessor_p.h\"\n"
    headerPrivate += "#include \"jsonhelper_p.h\"\n"

    headerPrivate += "\nnamespace QFB\n{\n\n"

    headerPrivate += createPrivateClass(className, False)


    headerPrivate += "}\n\n"
    headerPrivate += "#endif // QFB_" + className.upper() + "PROCESSOR_P_H\n"

    headerPrivateFile = open(className.lower() + "processor_p.h", "w")
    headerPrivateFile.write(headerPrivate)
    headerPrivateFile.close()

def createProperty(name, key, type):
    data = "    propertiesMap.insert(" + key + ", "

    if type == "QString":
        data += "jsonObject.value(" + key + ").toString()"
    elif type == "int":
        data += "(int) jsonObject.value(" + key + ").toDouble()"
    elif type == "QDateTime":
        data2 = "    QDateTime " + name + " = QDateTime::fromString(jsonObject.value("
        data2 += key + ").toString(), Qt::ISODate);\n"
        data = data2 + data
        data += name
    elif type == "QUrl":
        data += "parseUrl(jsonObject.value(" + key + ").toString())"
    else:
        data2 = "    // TODO: unknown type \"" + type + "\" for key \""  + key + "\". "
        data2 += "Template: \n"
        data2 += "    // " + data.strip() + " DATA"
        data = data2
    data += ");\n"
    return data

def createSource(className, includes, baseClass, variables, templateOnly):
    source = copyright

    source += "\n"
    source += "/**\n"
    source += " * @file " + className.lower() + "processor.cpp\n"
    source += " * @brief Implementation of QFB::" + className + "Processor\n"
    source += " */\n\n"
    source += "#include \"" + className.lower() + "processor.h\"\n"
    if not templateOnly:
        source += "#include \"" + className.lower() + "processor_p.h\"\n"
    source += "#include <QtCore/QCoreApplication>\n"
    source += "#include \"" + className.lower() + ".h\"\n"
    source += "#include \"" + className.lower() + "_keys_p.h\"\n"
    source += "#include \"helper_p.h\"\n"
    source += "#include \"namedobject_keys_p.h\"\n"
    source += "#include \"object_keys_p.h\"\n"
    if templateOnly:
        source += "#include \"jsonhelper_p.h\"\n"

    source += "\nnamespace QFB\n"
    source += "{\n\n"

    if templateOnly:
        source += createPrivateClass(className, True)

    source += className + "ProcessorPrivate::" + className + "ProcessorPrivate():\n"
    source += "    AbstractGraphProcessorPrivate()\n"
    source += "{\n"
    source += "    " + lowerCamelCase(className) + " = 0;\n"
    source += "}\n\n"

    if not templateOnly:
        source += className + " * " + className + "ProcessorPrivate::create" + className
        source += "(const JsonObject &jsonObject)\n"
        source += "{\n"
        source += "    PropertiesMap propertiesMap;\n"
        for variable in variables:
            if variable["name"].strip() != "" and variable["type"] != "TODO":
                splittedName = qfbtools.split(variable["name"].strip())
                key = qfbtools.staticKey(splittedName, className)
                if variable["name"] == "id":
                    key = "OBJECT_ID_KEY"
                elif variable["name"] == "name":
                    key = "NAMEDOBJECT_NAME_KEY"

                source += createProperty(qfbtools.camelCase(splittedName), key, variable["type"])


        source += "    " + className + " *" + lowerCamelCase(className) + " = new " + className
        source += "(propertiesMap);\n"
        source += "    " + lowerCamelCase(className)
        source += "->moveToThread(QCoreApplication::instance()->thread());\n"
        source += "    return " + lowerCamelCase(className) + ";\n"
        source += "}\n"


    source += "////// End of private class //////\n\n"

    source += className + "Processor::" + className + "Processor(QObject *parent):\n"
    source += "    AbstractGraphProcessor(*(new " + className + "ProcessorPrivate), parent)\n"
    source += "{\n"
    source += "}\n\n"

    source += className + " * " + className + "Processor::" + lowerCamelCase(className)
    source += "() const\n"
    source += "{\n"
    source += "    Q_D(const " + className + "Processor);\n"
    source += "    return d->" + lowerCamelCase(className) + ";\n"
    source += "}\n\n"

    source += "bool " + className + "Processor::processDataSource(QIODevice *dataSource)\n"
    source += "{\n"
    if templateOnly:
        source += "    // TODO: write the processing task here\n"
    else:
        source += "    Q_D(" + className + "Processor);\n\n"
        source += "    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);\n"
        source += "    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {\n"
        source += "        setError(\"Received data is not a JSON document\");\n"
        source += "        return false;\n"
        source += "    }\n"
        source += "    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);\n"
        source += "    d->" + lowerCamelCase(className) + " = d->create" + className
        source += "(rootObject);\n"
        source += "    if (d->" + lowerCamelCase(className) + ") {\n"
        source += "        return true;\n"
        source += "    } else {\n"
        source += "        return false;\n"
        source += "    }\n"

    source += "}\n\n"
    source += "}\n"


    sourceFile = open(className.lower() + "processor.cpp", "w")
    sourceFile.write(source)
    sourceFile.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='QFB object writer')
    parser.add_argument('input', metavar='input', type=str,
                        help="""Input file""")
    parser.add_argument('templateOnly', metavar='templateOnly', type=str,
                        help="""Only generate a template (y/n, default n)""")
    args = parser.parse_args()

    input = args.input
    templateOnly = False
    templateOnlyString = args.templateOnly
    if templateOnlyString == "y":
        templateOnly = True
    elif templateOnlyString != "n":
        print "Invalid input: \"" + templateOnlyString + "\""
        print "Will try to generate processor code"


    generate(input, templateOnly)


