def can_resolve(clause1, clause2):
    # 检查两个子句是否可以归结
    for lit1 in clause1:
        for lit2 in clause2:
            if lit1.strip('~') == lit2.strip('~') and (lit1.startswith('~') != lit2.startswith('~')):
                return True, lit1.strip('~')
    return False, None

def parse_clause(clause_str):
    # 将字符串形式的子句转换为元组
    return tuple(sorted(clause_str.strip('()').split(',')))

def format_clause(clause):
    # 格式化子句输出
    if not clause:
        return "()"
    return f"({','.join(clause)}),"

def find_resolution_pair(c1, c2):
    # 找出可以归结的文字对及位置
    letters = 'abcdefghijklmnopqrstuvwxyz'
    for lit1 in c1:
        for i, lit2 in enumerate(c2):
            if lit1.strip('~') == lit2.strip('~') and (lit1.startswith('~') != lit2.startswith('~')):
                return (lit1.strip('~'), f"{letters[i]}" if len(c2) > 1 else "")
    return None

def resolve(clause1, clause2, literal):
    # 执行单步归结
    result = []
    for lit in clause1:
        if lit.strip('~') != literal:
            result.append(lit)
    for lit in clause2:
        if lit.strip('~') != literal:
            result.append(lit)
    return tuple(sorted(set(result)))

def ResolutionProp(KB):
    # 初始化
    clauses = set()
    steps = []
    clause_dict = {}
    
    # 转换输入子句
    for i, clause in enumerate(KB, 1):
        atoms = parse_clause(clause)
        clauses.add(atoms)
        clause_dict[atoms] = i
        steps.append(f"{i} {format_clause(atoms)}")
    
    # 归结过程
    step_num = len(KB) + 1
    while True:
        new_clauses = set()
        # 获取所有可能的子句对
        pairs = [(c1, c2) for c1 in clauses for c2 in clauses if c1 < c2]
        
        found_new = False
        for c1, c2 in pairs:
            resolution_result = find_resolution_pair(c1, c2)
            if resolution_result:
                literal, pos_index = resolution_result
                resolvent = resolve(c1, c2, literal)
                
                if resolvent not in clauses and resolvent not in new_clauses:
                    # 记录归结步骤
                    step = f"{step_num} R[{clause_dict[c1]},{clause_dict[c2]}{pos_index}] = {format_clause(resolvent)}"
                    steps.append(step)
                    new_clauses.add(resolvent)
                    clause_dict[resolvent] = step_num
                    step_num += 1
                    found_new = True
                    
                    if not resolvent:  # 找到空子句
                        return steps
        
        if not found_new:  # 无法产生新的子句
            break
            
        clauses.update(new_clauses)
    
    return steps
