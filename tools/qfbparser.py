class ParserData:
    className = ""
    bassClass = ""
    includes = []
    variables = []

def _createGroup(groupData):
    splittedGroupData = groupData.strip().split("\n")
    group = {}

    # Check if it is a todo
    if len(splittedGroupData) == 1:
        group["name"] = splittedGroupData[0].strip()
        if group["name"] != "":
            group["type"] = "TODO"
        else:
            group["type"] = ""
        group["doc"] = ""
        return group


    # Extract the line containing name and type
    nameAndType = splittedGroupData[-1]
    splittedGroupData = splittedGroupData[:-1]
    splittedNameAndType = nameAndType.split(" ")

    group["name"] = splittedNameAndType[-1].strip()
    splittedNameAndType = splittedNameAndType[:-1]
    group["type"] = " ".join(splittedNameAndType).strip()
    group["doc"] = "\n".join(splittedGroupData).strip()
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
        return

    # Parse the first group (class name and includes)
    firstGroup = splittedData[0]
    del splittedData[0]

    splittedFirstGroup = firstGroup.strip().split("\n")
    if len(splittedFirstGroup) == 0:
        print """Error: the file is malformatted
The first group should have at least the name of the class"""

    parserData.className = splittedFirstGroup[0]
    for splittedFirstGroupItem in splittedFirstGroup:
        strippedSplittedItem = splittedFirstGroupItem.strip()
        if strippedSplittedItem != parserData.className and strippedSplittedItem != "":
            parserData.includes.append(strippedSplittedItem)

    for groupData in splittedData:
        parserData.variables.append(_createGroup(groupData))

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
    return parserData