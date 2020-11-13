import random
import subprocess
v = ["hello", "yesterday", "band", "bankers", "cat", "bat", "cab", "bugs", "mother", "daddy"]
def lookup(t, _v):
    if _v in t:
        c = t[_v]
        return "%s found, count = %s\n" % (_v, c)
    else:
        return "%s not found\n" % _v



def delete(t, _v):
    if _v in t:
        t[_v] = t[_v] - 1
        if t[_v] == 0:
            del t[_v]
            return "%s deleted\n" % _v
        return "%s deleted, new count = %s\n" % (_v, t[_v])
    else:
        return ""

def insert(t,_v):
    if _v in t:
        t[_v] = t[_v] + 1
    else:
        t[_v] = 1
    return "%s inserted, new count = %s\n" % (_v, t[_v])

def range_search(t, _v1, _v2):
    res = []
    for tt in t:
        if (tt <= _v2 and tt >= _v1):
            res.append(tt)
    res.sort()
    ress = ""
    for i in res:
        ress += "%s\n" % i
    return ress
current_loc = 0


while current_loc < 100000:
    current_loc += 1
    expected_result = ""
    stack = ""
    tree = {}
    for i in range(random.randint(100,1000)):
        u = random.randint(0, 12) % 4
        select = random.choice(v)
        if u == 0:
            expected_result += lookup(tree, select)
            stack += "lookup %s, " % select
        elif u == 1:
            expected_result += insert(tree, select)
            stack += "insert %s, " % select
        elif u == 2:
            expected_result += delete(tree, select)
            stack += "delete %s, " % select
        elif u == 3:
            v1 = random.choice(v)
            v2 = random.choice(v)
            expected_result += range_search(tree, v1, v2)
            stack += "range_search %s to %s, " % (v1, v2)
    stack = stack[:-2]
    try:
        result = subprocess.check_output(['./project1.out', stack])
        result = result.decode("utf-8")
        if result != expected_result:
            print(stack)
            print(expected_result)
            print(result)
    except:
        print("mem issue")
        print(stack)
        print(expected_result)
        print(result)
