import sys
steps = 0
maxNumber = 0
maxSteps = 0
def check(number):
    global steps
    sum = 1
    print("step {}: {}".format(steps,number))
    if (len(str(number)) <= 1):
        return number
    for x in str(number):
        sum *= int(x)
    steps += 1
    check(sum)
check(sys.argv[1])
print("steps:", steps)
# for y in range(10000000):
#     steps = 0
#     check(y)
#     if (steps > maxSteps):
#         maxSteps = steps
#         maxNumber = y
# print("Max:", maxNumber)
# print("steps:", maxSteps)