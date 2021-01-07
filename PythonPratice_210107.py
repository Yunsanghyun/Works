dict = {"씨발":"1","개새끼":"2","씨발새끼":"3"}

dict["씨발"] = 3
del dict["씨발"]

for a in dict:
    print("{} {}".format(a,dict[a]))