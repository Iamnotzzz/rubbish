
def parse_formula(formula):
    """解析原子公式，返回谓词和参数列表"""
    pred_end = formula.find('(')
    predicate = formula[:pred_end]
    args_str = formula[pred_end + 1:-1]
    args = [arg.strip() for arg in args_str.split(',')]
    return predicate, args

def is_variable(term):
    """判断是否为变量（以x、y、z、w开头的项）"""
    return term[0] in 'xyzw'

def is_function(term):
    """判断是否为函数项"""
    return '(' in term

def parse_function(func):
    """解析函数项，返回函数名和参数"""
    if not is_function(func):
        return func, []
    fname_end = func.find('(')
    fname = func[:fname_end]
    args_str = func[fname_end + 1:-1]
    args = [arg.strip() for arg in args_str.split(',')]
    return fname, args

def occurs_check(var, term, subst):
    """发生检测"""
    if var == term:
        return True
    if is_function(term):
        fname, args = parse_function(term)
        return any(occurs_check(var, arg, subst) for arg in args)
    if term in subst:
        return occurs_check(var, subst[term], subst)
    return False

def unify_terms(term1, term2, subst):
    """合一两个项"""
    # 应用已有替换
    if term1 in subst:
        return unify_terms(subst[term1], term2, subst)
    if term2 in subst:
        return unify_terms(term1, subst[term2], subst)
    
    # 变量处理
    if is_variable(term1):
        if occurs_check(term1, term2, subst):
            return None
        subst[term1] = term2
        return subst
    if is_variable(term2):
        if occurs_check(term2, term1, subst):
            return None
        subst[term2] = term1
        return subst
    
    # 函数项处理
    if is_function(term1) and is_function(term2):
        f1, args1 = parse_function(term1)
        f2, args2 = parse_function(term2)
        if f1 != f2 or len(args1) != len(args2):
            return None
        for a1, a2 in zip(args1, args2):
            subst = unify_terms(a1, a2, subst)
            if subst is None:
                return None
        return subst
    
    # 常量处理
    if term1 == term2:
        return subst
    return None

def MGU(formula1, formula2):
    """计算两个原子公式的最一般合一"""
    # 解析原子公式
    pred1, args1 = parse_formula(formula1)
    pred2, args2 = parse_formula(formula2)
    
    # 检查谓词是否相同
    if pred1 != pred2 or len(args1) != len(args2):
        return {}
    
    # 尝试合一
    subst = {}
    for arg1, arg2 in zip(args1, args2):
        result = unify_terms(arg1, arg2, subst)
        if result is None:
            return {}
        subst = result
    
    return subst


   