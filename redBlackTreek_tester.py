import numpy as np
import random

commands = ["add", "add", "add", "del"]
currentNodes = set()
# NodesVal = set()
f = open("redBlackTreeTest.txt", "w")

for i in range(10000):
    key = None
    val = None
    cmd = random.choice(commands)
    if(cmd == "add"):
        key = random.choice(range(1, 1000))
        val = random.choice(range(1, 1000))
        currentNodes.add(key)
        # NodesVal.add(val)
        print(f"{cmd} {key} {val}", file = f)
    elif(cmd == "del"):
        if(len(currentNodes) == 0):
            continue
        key = random.choice(list(currentNodes))
        currentNodes.remove(key)
        print(f"{cmd} {key}", file = f)
    
print("stop", file = f)