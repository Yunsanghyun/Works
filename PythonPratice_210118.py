import os

def find_file(path): 
    output = os.listdir(path)
    for item in output:
        if os.path.isdir(path + "/" + item):
            find_file(path + "/" + item)
        else:
            print("파일",path + "/" + item)

print("파일과 폴더 구분하기")
find_file(".")