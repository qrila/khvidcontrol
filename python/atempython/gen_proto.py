#!/bin/python
import sys
import re
#str="\tvoid setAuxSourceInput(uint8_t aUXChannel, uint16_t input);"

def argvars(args, isref):
    ref = isref and "&" or ""
    rv = ""
    for i in range(0, len(args) / 2 - 1):
        rv = rv + ref + rmstar(args[i*2+1]) + ", "

    last = len(args) / 2 - 1
    rv = rv + ref + rmstar(args[last*2+1])
    return rv

def argvars_ref(args):
    return argvars(args, True)

def gen(func, args):
    sys.stdout.write("static PyObject *" + func + "(PyObject *self, PyObject *args);")
    sys.stdout.write("\n")

def fix_ptrarg(args):
    rarr = []
    for v in args:
        if len(rarr) >= 1 and rarr[len(rarr) - 1] == "*":
            rarr.pop(len(rarr) - 1)
            v = "*" + v

        rarr.append(v)
    return rarr

f = open(sys.argv[1], 'r')
for str in f:
    match = re.search(".*void\ (set[a-zA-Z0-9]*)\((.*)\).*", str)
    if not match:
        continue

    func = match.group(1)
    arglist = match.group(2)
    args = re.findall("([*a-zA-Z0-9_]+)+", arglist)
    args = fix_ptrarg(args)
    gen(func, args)

