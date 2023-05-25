import numpy as np
import random

commands = ["add", "del"]
currentNodes = set()

f = open("redBlackTreeTest.txt", "w")

for i in range(1000):
    val = None
    cmd = random.choice(commands)
    if(cmd == "add"):
        val = random.choice(range(1, 1000))
        currentNodes.add(val)
        print(f"{cmd} {val}", file = f)
    elif(cmd == "del"):
        if(len(currentNodes) == 0):
            continue
        val = random.choice(list(currentNodes))
        currentNodes.remove(val)
        print(f"{cmd} {val}", file = f)
    
print("stop", file = f)