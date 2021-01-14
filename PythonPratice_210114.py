num = [52,346,423,456,2,3,4,6,346]

print("# (1) 요소 내부에 있는 값 찾기")
print("- {}는 {} 위치에 있습니다.".format(52,num.index(52)))
print()

print("# (2) 요소 내부에 없는 값 찾기")
number = 10000
try:
    print("- {}는 {} 위치에 있습니다.".format(number,num.index(number)))
except:
    print("- 리스트 내부에 없는 값 입니다.")
print()