#!/usr/bin/python3
#
# Generate a C++ class header and the compilation unit (the 'source file'). 
#
# Usage : generateClass.py class_name include_dir source_dir
# * class_name : should follow the CamelCase convention. The first char will be capitalized.
# * include_dir : path to the folder gathering the header files.
# * source_dir : path to the folder gathering the source files.

import sys
import re
import json

# check usage
if len(sys.argv) < 4:
    print('Usage : generateClass.py class_name include_dir source_dir')
    exit()
    pass

indexOfOutput=len(sys.argv) - 1
# parse args
targetClassName=sys.argv[1][0].upper() + sys.argv[1][1:]
targetIncludeDir=sys.argv[2]
targetSourceDir=sys.argv[3]

# tokenize the class name
def camel_case_split(identifier):
    matches = re.finditer('.+?(?:(?<=[a-z])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])|$)', identifier)
    return [m.group(0) for m in matches]


nameComponents = camel_case_split(targetClassName)
guardComponents = [c.upper() for c in nameComponents]
guardComponents.extend(['HPP'])
guardName = '_'.join(guardComponents)

# generate header file

with open(targetIncludeDir+'/'+targetClassName+'.hpp', 'w') as outfile:
    outfile.writelines('#ifndef '+guardName+'\n')
    outfile.write('#define '+guardName+'\n')
    outfile.write('\n')
    outfile.write('// standard includes\n')
    outfile.write('#include <cstdint>\n')
    outfile.write('\n')
    outfile.write('// esp32 includes\n')
    outfile.write('\n')
    outfile.write('// project includes\n')
    outfile.write('\n')
    outfile.write('/** @brief What the class is for.\n')
    outfile.write(' */\n')
    outfile.write('class '+targetClassName + ' {\n')
    outfile.write('    private:\n')
    outfile.write('\n')
    outfile.write('    public:\n')
    outfile.write('        virtual ~'+targetClassName+'() ;\n')
    outfile.write('\n')
    outfile.write('} ;\n')
    outfile.write('\n')
    outfile.write('#endif')


with open(targetSourceDir+'/'+targetClassName+'.cpp', 'w') as outfile:
    outfile.write('\n')
    outfile.write('// header include\n')
    outfile.write('#include "'+ targetClassName +'.hpp"\n')
    outfile.write('\n')
    outfile.write(targetClassName +'::~'+ targetClassName +'(){}\n')
    outfile.write('// write code here...\n')
    outfile.write('\n')

