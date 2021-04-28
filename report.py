#!/usr/bin/python3

import os
import re

# Generate performance report table from the measurements listed in the codes

def report(src, type) :
    ext = re.sub("^.*\.", "", src);
    label = "// BENCH";
    if ext == "py" :
        label = "# BENCH";

    result = []

    lines = os.popen("cat \"{}\" | grep \"{}\"".format(src, label)).read().split("\n");
    for line in lines :
        line = re.sub("{} ".format(label), "", line);

        match = re.search("{}\s(?P<VALUE>.*)".format(type), line)
        if match :
            result.append(match.group("VALUE"));

    return result


srcs = os.popen("find src/tests -name \"arrsin*\"").read().split("\n");

print("Name | Time | Check | Executable");

for src in srcs :
    if src == "" :
        continue
    names = report(src, "NAME");
    times = report(src, "SCORE");
    checks = report(src, "CHECK");
    executables = report(src, "EXEC");

    for i in range(len(names)) :
        print("{} | {} | {} | {}".format(names[i], times[i], checks[i], executables[i]));

