from ResolutionProp import ResolutionProp
from mgu import MGU

if __name__ == "__main__":
    # 测试命题逻辑归结
    print("命题逻辑归结测试：")
    KB1 = ['(FirstGrade,)', '(~FirstGrade,Child)', '(~Child,)']
    print("测试用例1：")
    steps = ResolutionProp(KB1)
    for step in steps:
        print(step)
    
    print("\n命题逻辑归结测试2：")
    KB2 = [
        '(A,B,C)',
        '(~A,D)',
        '(~B,~C)',
        '(~D,)'
    ]
    print("测试用例2：")
    steps = ResolutionProp(KB2)
    for step in steps:
        print(step)
    
    print("\n最一般合一算法测试：")
    # 测试用例1
    result1 = MGU('P(xx,a)', 'P(b,yy)')
    print("Test 1:", result1)  # 应输出: {'xx': 'b', 'yy': 'a'}
    
    # 测试用例2
    result2 = MGU('P(a,xx,f(g(yy)))', 'P(zz,f(zz),f(wj))')
    print("Test 2:", result2)  # 应输出: {'zz': 'a', 'xx': 'f(a)', 'wj': 'g(yy)'}
    
    
    print("\n谓词逻辑归结测试 - 示例：")
    KB4 = [
        '(On(tony,mike),)',
        '(On(mike,john),)',
        '(Green(tony),)',
        '(~Green(john),)',
        '(~On(xx,yy),~Green(xx),Green(yy))'
    ]
    print("测试用例4：")
    steps = ResolutionProp(KB4)
    for step in steps:
        print(step)
