#!/bin/python
import sys
import re
#str="\tvoid setAuxSourceInput(uint8_t aUXChannel, uint16_t input);"

def format_map(name):
    if (name == "uint16_t"):
        return "h"

    if (name == "uint8_t"):
        return "b"

    if (name == "int"):
        return "i"

    if (name == "long"):
        return "l"

    if (name == "char"):
        return "b"

    if (name == "bool"):
        return "i"

    return name

def fullarg_vars(args):
    rv = ""
    for i in range(0, len(args) / 2):
        rv = rv + "\t" + args[i*2] + " " + args[i*2+1] + ";\n"
    return rv

def format_list(args):
    rv = ""
    for i in range(0, len(args) / 2):
        rv = rv + format_map(args[i*2])
    return rv

def rmstar(v):
    if (v[0] == "*"):
        return v[1:]

    return v

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
    sys.stdout.write("static PyObject *")
    sys.stdout.write(func)
    sys.stdout.write("(PyObject *self, PyObject *args) {\n")
    sys.stdout.write(fullarg_vars(args))
    sys.stdout.write("\n")

    # parsetuple
    sys.stdout.write("\tif (!PyArg_ParseTuple(args, \"")
    sys.stdout.write(format_list(args))
    sys.stdout.write("\", ")
    sys.stdout.write(argvars_ref(args))
    sys.stdout.write(")) {\n")
    sys.stdout.write("\t\treturn NULL;\n")
    sys.stdout.write("\t}\n\n")

    # call
    sys.stdout.write("\tAtemSwitcher." + func + "(" + argvars(args, False) + ");\n")

    # end
    sys.stdout.write("\tPy_INCREF(Py_None);\n")
    sys.stdout.write("\treturn Py_None;\n")
    sys.stdout.write("}\n\n")

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

