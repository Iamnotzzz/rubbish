def parse_atom(atom):
    """解析原子公式为谓词和参数列表，正确处理嵌套括号"""
    atom = atom.replace(' ', '')  # 去除空格
    if ('(' not in atom):
        return (atom, [])
    
    # 分离谓词和参数字符串
    pred_end = atom.find('(')
    pred = atom[:pred_end]
    args_str = atom[pred_end + 1:-1]  # 去掉最外层括号
    
    # 智能分割参数，考虑嵌套括号
    args = []
    current_arg = ""
    paren_level = 0
    
    for char in args_str:
        if char == ',' and paren_level == 0:
            args.append(current_arg)
            current_arg = ""
        else:
            if char == '(':
                paren_level += 1
            elif char == ')':
                paren_level -= 1
            current_arg += char
    
    if current_arg:
        args.append(current_arg)
    
    return (pred, args)

def is_variable(term):
    """判断一个项是否是变量（以小写字母开头的符号）"""
    return term and term[0].islower() and '(' not in term

def occurs_check(var, term):
    """检查变量是否出现在项中"""
    # 确保检查的是1-2个字母的变量
    if not is_variable(var):
        return False
        
    if (var == term):
        return True
    if ('(' in term):
        (_, args) = parse_atom(term)
        return any((occurs_check(var, arg) for arg in args))
    return False

def unify_var(var, x, subst):
    """处理变量替换"""
    if var in subst:
        return unify(subst[var], x, subst)
    elif x in subst:
        return unify(var, subst[x], subst)
    elif occurs_check(var, x):
        return None
    else:
        # 创建新的替换字典以避免修改原字典
        new_subst = subst.copy()
        new_subst[var] = x
        
        # 更新其他变量的替换，将var替换为x
        for k, v in new_subst.items():
            if k != var:  # 跳过刚添加的替换
                new_subst[k] = apply_substitution(v, {var: x})
        
        return new_subst

def unify(a1, a2, subst=None):
    """递归合一两个项"""
    if (subst is None):
        subst = {}
    if (a1 == a2):
        return subst
    # 修改为使用新的变量识别函数
    if is_variable(a1):
        return unify_var(a1, a2, subst)
    if is_variable(a2):
        return unify_var(a2, a1, subst)
    if (('(' in a1) and ('(' in a2)):
        (pred1, args1) = parse_atom(a1)
        (pred2, args2) = parse_atom(a2)
        if ((pred1 != pred2) or (len(args1) != len(args2))):
            return None
        for (x, y) in zip(args1, args2):
            subst = unify(x, y, subst)
            if (subst is None):
                return None
        return subst
    return None

def MGU(atom1, atom2):
    """最一般合一算法"""
    # 检查是否为互补字面量
    neg1 = atom1.startswith('~')
    neg2 = atom2.startswith('~')
    
    if neg1 != neg2:
        a1 = atom1[1:] if neg1 else atom1
        a2 = atom2[1:] if neg2 else atom2
        if a1 == a2:
            return None  # 互补字面量无法合一
    
    # 提取原子公式
    a1 = atom1[1:] if neg1 else atom1
    a2 = atom2[1:] if neg2 else atom2
    
    # 执行合一
    subst = unify(a1, a2)
    if not subst:
        return subst
    
    # 进行完全的替换，确保所有变量都被替换到最终形式
    # 循环应用替换直到没有变化为止
    changed = True
    while changed:
        changed = False
        final_subst = {}
        
        for var in subst:
            new_term = apply_substitution(subst[var], subst)
            final_subst[var] = new_term
            if new_term != subst[var]:
                changed = True
        
        subst = final_subst.copy()
    
    return subst

def apply_substitution(term, subst):
    """应用替换到项上，确保完全替换"""
    if not subst:
        return term
    
    # 处理变量的情况
    if is_variable(term) and term in subst:
        # 获取替换后的结果
        result = subst[term]
        # 递归应用替换，直到结果不再变化
        next_result = apply_substitution(result, subst)
        return next_result
    
    # 处理常量的情况
    if '(' not in term:
        return term
    
    # 处理复合项
    pred, args = parse_atom(term)
    new_args = [apply_substitution(arg, subst) for arg in args]
    return f"{pred}({','.join(new_args)})"
