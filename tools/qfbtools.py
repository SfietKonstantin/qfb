def isPointer(name):
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
