import numpy as np
import random

commands = ["add", "del"]
currentNodes = set()
# NodesVal = set()
f = open("redBlackTreeTest.txt", "w")
n = 10000
weights = [0.75, 0.25]

for i in range(n):
    key = None
    val = None
    if(n%250 == 0):
        weights = weights[::-1]
        # print(weights)
    cmd = random.choices(commands, weights = weights)[0]
    if(cmd == "add"):
        key = random.choice(range(1, 1000))
        # val = random.choice(range(1, 1000))
        val = key
        currentNodes.add(key)
        # NodesVal.add(val)
        print(f"{cmd} {key} {val}", file = f)
    elif(cmd == "del"):
        if(len(currentNodes) == 0):
            continue
        key = random.choice(list(currentNodes))
        currentNodes.remove(key)
        print(f"{cmd} {key}", file = f)
    
print("stop 1", file = f)