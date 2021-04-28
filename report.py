#!/usr/bin/python3

import os
import re

# Generate performance report table from the measurements listed in the codes

def report(src, type) :
    ext = re.sub("^.*\.", "", src);
    label = "// BENCH";
    if ext == "py" :
        label = "# BENCH";

    lines = os.popen("cat \"{}\" | grep \"{}\"".format(src, label)).read().split("\n");
    for line in lines :
        line = re.sub("{} ".format(label), "", line);

        match = re.search("{}\s(?P<VALUE>.*)".format(type), line)
        if match :
            return match.group("VALUE");

    return "{src} UNDEFINED";


srcs = os.popen("find src/tests -name \"arrsin*\"").read().split("\n");

print("Name | Time | Check | Executable");

for src in srcs :
    if src == "" :
        continue
    name = report(src, "NAME");
    time = report(src, "SCORE");
    check = report(src, "CHECK");
    executable = report(src, "EXEC");

    print("{} | {} | {} | {}".format(name, time, check, executable));

