from mgu import MGU
from resolution import ResolutionFOL

if (__name__ == '__main__'):
    
    
    print('\n==== MGU测试 ====')
    print(MGU('P(xx,a)', 'P(b,yy)'))
    print(MGU('P(a,xx,f(g(yy)))', 'P(zz,f(zz),f(uu))'))
    
    print('\n==== 一阶逻辑测试（Alpine Club） ====')
    # 示例1: 硕士生问题
    print('\n示例1: 硕士生问题')
    KB1 = {('GradStudent(sue)',), ('~GradStudent(x)', 'Student(x)'), ('~Student(x)', 'HardWorker(x)'),
           ('~HardWorker(sue)',)}
    steps1 = ResolutionFOL(KB1)
    for step in steps1:
        print(step)
    
    # 示例2: Alpine Club问题
    print('\n示例2: Alpine Club问题')
    KB2 = {('A(tony)',), ('A(mike)',), ('A(john)',), ('L(tony,rain)',), ('L(tony,snow)',), ('~A(x)', 'S(x)', 'C(x)'),
           ('~C(y)', '~L(y,rain)'), ('L(z,snow)', '~S(z)'), ('~L(tony,u)', '~L(mike,u)'), ('L(tony,v)', 'L(mike,v)'),
           ('~A(w)', '~C(w)', 'S(w)')}
    steps2 = ResolutionFOL(KB2)
    for step in steps2:
        print(step)
    
    # 示例3: 颜色问题
    print('\n示例3: 颜色问题')
    KB3 = {('On(tony,mike)',), ('On(mike,john)',), ('Green(tony)',), ('~Green(john)',),
           ('~On(xx,yy)', '~Green(xx)', 'Green(yy)')}
    steps3 = ResolutionFOL(KB3)
    for step in steps3:
        print(step)