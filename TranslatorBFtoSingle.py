
import sys

def main(origin):
    table = {'>' : 0,'<' : 1, '+' : 2, 
             '-' : 3,'.' : 4,',' : 5,'[' : 6,']' : 7}
    translated = ''
    dv = -1
    for op in origin:
        translated += '0' * (7 - dv)
        translated += '0' * table[op] + 's'
        dv = table[op]
    print(translated)

if __name__ == '__main__':
    main(sys.argv[1])