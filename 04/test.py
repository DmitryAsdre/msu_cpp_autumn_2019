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
file = open("samples.dat", 'r')
for string in file:
    string = string.rstrip("\n")
    args = string.split(sep = " ")
    lexem = " \"" + args[1]  + "\" "
    command = "./test " + str(args[0]) + lexem + str(args[2])
    test(command, 0, [args[3]])
