import re

def is_delimiter(x):
    c = ord(x) #ASCII
    if c == 10 or c == 11 or c == 32 or c == 37 or c ==38 or (c>=40 and c<=45) or c==47 or (c>=59 and c<=62) or c==124:
        return True
    return False

def check_valid(exp):
    if len(exp):
        if re.match('^[+-]?[1-9][0-9]+(U|L|(ULL)|(UL))?$', exp): #Integer
            return 'integer'
        elif re.match('^[0-7]+$', exp): #Octal
            return 'octal'
        elif re.match('^(0x){1}([0-9]|[a-f]|[A-F])+$', exp): #Hexa
                return 'hexa'
        elif re.match('^[+-]?(\d+\.\d+)([eE][+-]?\d+)?$', exp): #float
            return 'float'
        elif re.match('\'.\'', exp): #char - TO DO: esc seq?
            return 'char'
        elif re.match('\"(.*)\"', exp):
            return 'string'

    return False

def check_n_write(exp):
    ret = check_valid(exp)
    if ret:
        if ret == 'string' or ret == 'char':
            write_file.write(exp[1:len(exp)-1] + '\n')
        else:
            write_file.write(exp + '\n')
        string_mode = False
        esc = False


source_file = open('test_file.c', 'r')
write_file = open('literals.txt', 'w')

for line in source_file:
    exp = ''
    esc = False
    string_mode = False

    for alpha in line:
        if esc:
            exp += alpha
            esc = False

        elif alpha == '\"':
            if string_mode:
                exp += alpha
                check_n_write(exp)
                exp = ''
            else:
                string_mode = True
                exp += alpha

        elif string_mode and alpha == '\\':
            esc = True

        elif string_mode:
            exp += alpha

        elif not is_delimiter(alpha):
            exp += alpha
        else:
            check_n_write(exp)
            exp = ''

    check_n_write(exp)

source_file.close()
write_file.close()