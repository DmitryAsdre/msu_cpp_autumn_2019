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
test('./main 1000 100 100 100', 0, ['100 100 100'])
test('./main 1000 1000', 0, ['1000'])
test('./main 1000 1001', 0, ['nullptr'])
test('./main 1000 100 1000', 0, ['100 nullptr'])
test('./main 1000 100 -1 1000', 0, ['100 1000'])