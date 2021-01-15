def test():
    try:
        a = float(input("정수를 입력해달라니깐?"))
        return
    except:
        print("error")
        return    
    finally:
        print("어쨰든 여기까지 왔네")

test()