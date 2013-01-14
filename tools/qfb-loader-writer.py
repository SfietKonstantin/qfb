#!/usr/bin/python
#
# This tool is used to quickly create loader
# that are used to expose Facebook objects to
# a QML context
#
import argparse
import string
import re
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

def generate(className, loadedClass):
    createHeader(className, loadedClass)
    createSource(className, loadedClass)

def createHeader(className, loadedClass):
    header = copyright
    header += "\n"
    header += "#ifndef QFB_" + className.upper() + "_H\n"
    header += "#define QFB_" + className.upper() + "_H\n\n"
    header += "/**\n"
    header += " * @file " + className.lower() + ".h\n"
    header += " * @brief Definition of QFB::" + className + "\n"
    header += " */\n\n"

    header += "#include \"abstractgraphloader.h\"\n\n"

    header += "namespace QFB\n{\n\n"
    header += "class " + loadedClass + ";\n"
    header += "class " + className + "Private;\n"
    header += "/**\n"
    header += " * @short WRITE DOCUMENTATION HERE\n"
    header += " */\n"
    header += "class QFBBASEIMPORT_EXPORT " + className + ": public AbstractGraphLoader\n{\n"
    header += "    Q_OBJECT\n"
    header += "    /**\n"
    header += "     * @brief " + loadedClass +"\n"
    header += "     */\n"
    header += "    Q_PROPERTY(QFB::" + loadedClass + " * "
    header += qfbtools.lowerCamelCase(loadedClass)
    header += " READ " + qfbtools.lowerCamelCase(loadedClass)
    header += " NOTIFY " + qfbtools.lowerCamelCase(loadedClass) + "Changed)\n"
    header += "public:\n"
    header += "    /**\n"
    header += "     * @brief Default constructor\n"
    header += "     * @param parent parent object.\n"
    header += "     */\n"
    header += "    explicit " + className + "(QObject *parent = 0);\n"
    header += "    /**\n"
    header += "     * @brief " + loadedClass +"\n"
    header += "     * @return " + qfbtools.lowerCamelCase(loadedClass) +".\n"
    header += "     */\n"
    header += "    " + loadedClass + " * " + qfbtools.lowerCamelCase(loadedClass)
    header += "() const;\n"
    header += "Q_SIGNALS:\n"
    header += "    /**\n"
    header += "     * @brief " + loadedClass +" changed\n"
    header += "     */\n"
    header += "    void " + qfbtools.lowerCamelCase(loadedClass) + "Changed();\n"
    header += "protected:\n"
    header += "    /**\n"
    header += "     * @brief Implementation of AbstractGraphLoader::createRequest()\n"
    header += "     * @param graph Graph.\n"
    header += "     * @param arguments Arguments.\n"
    header += "     * @return Created request.\n"
    header += "     */\n"
    header += "     Request createRequest(const QString &graph, const QString &arguments);\n"
    header += "    /**\n"
    header += "     * @brief Implementation of AbstractLoader::handleReply()\n"
    header += "     * @param processor Processor to handle.\n"
    header += "     */\n"
    header += "     void handleReply(AbstractProcessor *processor);\n"
    header += "private:\n"
    header += "    Q_DECLARE_PRIVATE(" + className + ")\n"
    header += "};\n\n"
    header += "}\n\n"
    header += "#endif // QFB_" + className.upper() + "_H\n"

    headerFile = open(className.lower() + ".h", "w")
    headerFile.write(header)
    headerFile.close()

def createSource(className, loadedClass):
    source = copyright
    source += "\n"
    source += "/**\n"
    source += " * @file " + className.lower() + ".cpp\n"
    source += " * @brief Implementation of QFB::" + className + "\n"
    source += " */\n\n"
    source += "#include \"" + className.lower() + ".h\"\n"
    source += "#include \"private/abstractloader_p.h\"\n"
    source += "#include \"querymanager.h\"\n"
    source += "#include \"processors/objectprocessor.h\"\n\n"
    source += "#include \"objects/" + loadedClass.lower() + ".h\"\n"

    source += "namespace QFB\n"
    source += "{\n\n"

    source += "class " + className + "Private: public AbstractLoaderPrivate\n"
    source += "{\n"
    source += "public:\n"
    source += "    " + className + "Private(" + className + " *q);\n"
    source += "    " + loadedClass + " *" + qfbtools.lowerCamelCase(loadedClass) + ";\n"
    source += "};\n\n"

    source += className + "Private::" + className + "Private(" + className +" *q):\n"
    source += "    AbstractLoaderPrivate(q)\n"
    source += "{\n"
    source += "    " + qfbtools.lowerCamelCase(loadedClass) + " = 0;\n"
    source += "}\n\n"

    source += "////// End of private class //////\n\n"

    source += className + "::" + className + "(QObject *parent):\n"
    source += "    AbstractGraphLoader(*(new " + className +"Private(this)), parent)\n"
    source += "{\n"
    source += "}\n\n"

    source += loadedClass + " * " + className + "::" + qfbtools.lowerCamelCase(loadedClass)
    source += "() const\n"
    source += "{\n"
    source += "    Q_D(const " + className + ");\n"
    source += "    return d->" + qfbtools.lowerCamelCase(loadedClass) + ";\n"
    source += "}\n\n"

    source += "Request " + className
    source += "::createRequest(const QString &graph, const QString &arguments)\n"
    source += "{\n"
    source += "    if (queryManager()) {\n"
    source += "        return queryManager()->queryObject(Object::" + loadedClass + "Type, "
    source += "graph, arguments);\n"
    source += "    }\n"
    source += "    return Request();\n"
    source += "}\n\n"

    source += """void """ + className + """::handleReply(AbstractProcessor *processor)
{
    Q_D(""" + className + """);
    ObjectProcessor *objectProcessor = qobject_cast<ObjectProcessor *>(processor);
    if (d->""" + qfbtools.lowerCamelCase(loadedClass) + """) {
        d->""" + qfbtools.lowerCamelCase(loadedClass) + """->deleteLater();
    }

    d->""" + qfbtools.lowerCamelCase(loadedClass) + """ = qobject_cast<"""
    source += loadedClass + """*>(objectProcessor->object());
    d->""" + qfbtools.lowerCamelCase(loadedClass) + """->setParent(this);
    emit """ + qfbtools.lowerCamelCase(loadedClass) + """Changed();
}

"""

    source += "}\n"


    sourceFile = open(className.lower() + ".cpp", "w")
    sourceFile.write(source)
    sourceFile.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='QFB loader writer')
    parser.add_argument('className', metavar='className', type=str,
                        help="""Class name""")
    parser.add_argument('loadedClass', metavar='loadedClass', type=str,
                        help="""Loaded class""")
    args = parser.parse_args()

    className = args.className
    loadedClass = args.loadedClass
    generate(className, loadedClass)


