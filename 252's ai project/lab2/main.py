from ResolutionProp import ResolutionProp

if __name__ == "__main__":
    # 测试用例1：简单归结
    KB1 = ['(FirstGrade,)', '(~FirstGrade,Child)', '(~Child,)']
    print("测试用例1：")
    steps = ResolutionProp(KB1)
    for step in steps:
        print(step)
        
    # 测试用例2：复杂子句
    KB2 = ['(A,B,C)', '(~A,D)', '(~B,~C)', '(~D,)']
    print("\n测试用例2：")
    steps = ResolutionProp(KB2)
    for step in steps:
        print(step)