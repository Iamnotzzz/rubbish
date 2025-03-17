def parse_clause(clause_str):
    return tuple(sorted(clause_str.strip('()').split(',')))

def format_clause(clause):
    return "()" if not clause else f"({','.join(clause)}),"

def resolve(c1, c2):
    for lit1 in c1:
        for i, lit2 in enumerate(c2):
            if lit1.strip('~') == lit2.strip('~') and (lit1.startswith('~') != lit2.startswith('~')):
                # 返回可归结的文字和位置索引
                result = []
                literal = lit1.strip('~')
                for lit in c1 + c2:
                    if lit.strip('~') != literal:
                        result.append(lit)
                return True, tuple(sorted(set(result))), (literal, 'abcdefghijklmnopqrstuvwxyz'[i] if len(c2) > 1 else "")
    return False, None, (None, "")  # 修改这里，确保返回一致的元组结构

def ground_literal(literal, subst):
    if not ('(' in literal and ')' in literal):
        return literal
    neg = literal.startswith('~')
    lit = literal.strip('~')
    pred_end = lit.find('(')
    args = [subst.get(arg.strip(), arg.strip()) for arg in lit[pred_end + 1:-1].split(',')]
    result = f"{lit[:pred_end]}({','.join(args)})"
    return '~' + result if neg else result

def instantiate_KB(KB):
    from mgu import MGU
    grounded_KB = []
    subst_history = {}
    
    for clause in KB:
        atoms = parse_clause(clause)
        grounded_KB.append(f"({','.join(ground_literal(lit, subst_history) for lit in atoms)})")
        
        # 更新替换历史
        for lit in atoms:
            if '(' in lit and ')' in lit and any(c in lit for c in 'xyzw'):
                for prev_lit in subst_history:
                    if '(' in prev_lit:
                        subst = MGU(lit.strip('~'), prev_lit.strip('~'))
                        if subst:
                            subst_history.update(subst)
    return grounded_KB

def ResolutionProp(KB):
    # 谓词逻辑例化
    if any('(' in lit and ')' in lit for clause in KB for lit in parse_clause(clause)):
        KB = instantiate_KB(KB)
    
    clauses = set()
    steps = []
    clause_dict = {}
    
    # 初始化子句集
    for i, clause in enumerate(KB, 1):
        atoms = parse_clause(clause)
        clauses.add(atoms)
        clause_dict[atoms] = i
        steps.append(f"{i} {format_clause(atoms)}")
    
    # 归结过程
    step_num = len(KB) + 1
    while True:
        new_clauses = set()
        found_new = False
        
        for c1 in clauses:
            for c2 in clauses:
                if c1 >= c2: continue
                can_resolve, resolvent, (literal, pos_index) = resolve(c1, c2)
                
                if can_resolve and resolvent not in clauses and resolvent not in new_clauses:
                    steps.append(f"{step_num} R[{clause_dict[c1]},{clause_dict[c2]}{pos_index}] = {format_clause(resolvent)}")
                    new_clauses.add(resolvent)
                    clause_dict[resolvent] = step_num
                    step_num += 1
                    found_new = True
                    
                    if not resolvent:  # 空子句
                        return steps
        
        if not found_new:
            break
        clauses.update(new_clauses)
    
    return steps


