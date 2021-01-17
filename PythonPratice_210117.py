student = [
    {"이름":"윤상현", "나이":30},
    {"이름":"윤수현", "나이":28}
]

class Student:
    def __init__(self,이름,나이):
        self.이름 = 이름
        self.나이 = 나이
    
    def ret(self):
        return {"이름":self.이름,"나이":self.나이}

    def print(self):
        print(self.이름, self.나이)
        
test = Student("윤승현",23)
student.append(test.ret())
print(student)

