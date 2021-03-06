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
test('./calc ""', 1, ['unexpected_end'])
test('./calc " "', 1, ['unexpected_end'])
test('./calc "                 "', 1, ['unexpected_end'])
test('./calc "()"', 1, ['brackets_error'])
test('./calc ")"', 1, ['brackets_error'])
test('./calc "("', 1, ['unexpected_end'])
test('./calc "+"', 1, ['binary_operator_error'])
test('./calc "-"', 1, ['unexpected_end'])
test('./calc "/"', 1, ['binary_operator_error'])
test('./calc "-12 3"', 1, ['num_error'])
test('./calc "2"', 0, [ '2' ])
test('./calc "1+1"', 0, ['2'])
test('./calc "2"', 0, [ '2' ])
test('./calc "-2"', 0, [ '-2' ])
test('./calc "2 + 2"', 0, [ '4' ])
test('./calc "2 + 2   "', 0, [ '4' ])
test('./calc "2 + 3 * 4 - -2"', 0, ['16'])
test('./calc "2 +- 2"', 0, [ '0' ])
test('./calc "   2+-4"', 0, [ '-2' ])
test('./calc "-    4- -4"', 0, [ '0' ])
test('./calc "2-3*4+-5/2"', 0, [ '-12.5' ])
test('./calc "2-3*4*2+1--2+-5/2"', 0, [ '-21.5' ])
test('./calc', 1, [ 'unexpected_input' ])
test('./calc 2 + 3', 1, [ 'unexpected_input' ])
test('./calc "2/0"', 1, [ 'division_by_0' ])
test('./calc "2/"', 1, [ 'unexpected_end' ])
test('./calc "3 + a"', 1, [ 'unknown_lexem' ])
test('./calc "(1+2+3-5)*10 - 14 + 2"', 0, ['-2'])
test('./calc "(1+2+3-5)*10 - 14*-2"', 0, ['38'])
test('./calc "10*(11 - (22*14 + 5))*10"', 0, ['-30200'])
test('./calc "6 - (10*10 + 100/2)*3"', 0, ['-444'])
test('./calc "(10*10 + -1)*(1 - 10)"', 0, ['-891'])
test('./calc "(10*10 + 1))"', 1, ['brackets_error'])
test('./calc "1----1"', 0, ['2'])
test('./calc "1-----1"', 0, ['0'])
test('./calc "1+(2 - 3 +) +"', 1, ['brackets_error'])
test('./calc "1 - 2*3 + 4"', 0, ['-1'])
test('./calc "10 ++ 1"', 1, ['binary_operator_error'])
test('./calc "4*-(10*(5)) - 4"', 0, ['-204'])
test('./calc "1-10+3 4"', 1, ['num_error'])
test('./calc "12*12*4*+4"', 1, ['binary_operator_error'])
test('./calc "4+12+-4/(1-1)"', 1,['division_by_0'])
test('./calc "51/(24 - (8*3)))"', 1, ['division_by_0'])
test('./calc "((((5 + 4))))"', 0, ['9'])
test('./calc "((-(4 + 0) + 4 )*20)"', 0, ['0'])
test('./calc "((((((((((1.3444))))))))))"', 0, ['1.3444'])
test('./calc "((((((((((1.3444))))))))))()"', 1, ['brackets_error'])