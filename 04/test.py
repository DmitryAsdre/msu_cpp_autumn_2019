import subprocess as sb
import time 
def run(command):
    process = sb.Popen(command, shell=True, stdout=sb.PIPE, stderr=sb.STDOUT)
    out = process.stdout.readlines()
    code = process.wait()
    return code, out
def test(command, expected_code, expected_value):
    print(command)
    code, out = run(command)
    if code != expected_code:
        print ('return value', expected_code, '(expected) !=', code)
        return
    out = map(lambda x: str(x, 'utf-8'), out)
    i = 0
    for line in out:
        try:
            if line.rstrip() != expected_value[i]:
                print (expected_value[i], '(expected) !=', line.rstrip())
                time.sleep(10)
                return
            i += 1
        except ValueError:
            print ('invalid output')
            return
        except IndexError:
            print ('invalid output')
            return
    if i != len(expected_value):
        print ('empty output')
        return
    print ('ok') 
test("./test \"-\" 0", 0, ["0"])
test("./test 1233b \"-\" 1233", 1, ["unexpected input"])
test("./test -100 + 100", 0, ["0"])
test("./test 100 - 100", 0, ["0"])
test("./test 1000 + -1000", 0, ["0"])
file = open("samples.dat", 'r')
for string in file:
    string = string.rstrip("\n")
    args = string.split(sep = " ")
    if(len(args) == 4):
        lexem = " \"" + args[1]  + "\" "
        command = "./test " + str(args[0]) + lexem + str(args[2])
        res = [args[3]]
    else:
        lexem = " \"" + args[1] + "\" ";
        command = "./test " + lexem + str(args[1])
        res = [args[2]]
    test(command, 0, res)
