import argparse

parser = argparse.ArgumentParser(description='命令行参数学习')
# parser.add_argument('-f','--file',help='input file')
parser.add_argument('-f','--file',help='密码文件')
args = parser.parse_args()

if args.file:
    print(args.file)

