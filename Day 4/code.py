#input: 240298-784956
#Rules:
#from left to right numbers only increase
#code must contain a double e.g. 122345
#therefore:
#788888 is not a possibility so max is 777777
#222222 is not a possibility so min is 244444

all_possibilities = range(244444, 788888)
possible_codes = []
def check_double(num):
    string = str(num)
    counts = {}
    for x in range(len(string)):
        if string[x] in counts:
            counts[string[x]] += 1
        else:
            counts[string[x]] = 1
    for key in counts:
        if counts[key] == 2:
            return True
    return False

def check_increase(num):
    string = str(num)
    for x in range(1, len(string)):
        if string[x-1] > string[x]:
            return False
    return True


for x in all_possibilities:
    if check_double(x):
        if(check_increase(x)):
            possible_codes.append(x)

print(len(possible_codes))

