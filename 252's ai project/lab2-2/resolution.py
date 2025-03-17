import copy

# 公式类
class fml:
    def __init__(self, ifnot, predicate, parameter):
        # 是否~,0代表非，1代表正
        self.ifnot = ifnot
        # 谓词（字符串）
        self.predicate = predicate
        # 参数列表（包括变量或者常量）
        self.parameter = parameter

    def print_for(self):
        str = ''
        if self.ifnot == 0:#是否取反
            str += '~'
        str += self.predicate#谓词
        str += '('
        for j in range(len(self.parameter)):
            str += self.parameter[j]
            if j < len(self.parameter) - 1:
                str += ','
        str += ')'
        return str

def list_to_str(list0):
    """将列表转换为字符串表示，处理fml对象的特殊情况"""
    if not list0:
        return "()"
    
    # 检查是否包含fml对象
    if isinstance(list0[0], fml):
        # 将每个fml对象转换为其字符串表示
        formula_strs = [f.print_for() for f in list0]
        return str(tuple(formula_strs))
    else:
        # 原始行为：直接将列表转换为元组再转为字符串
        return str(tuple(list0))

def if_list_in(list0, KB):#判断子句list0是否在子句集KB中，避免重复归结（0代表KB中存在list0，1代表KB中不存在list0）
    n = len(KB)
    for i in range(n):
        if KB[i] == list0:
            return 0
    return 1

#归结函数
def resolution(list1, list2, list1_index, list2_index, KB, step, result):
    m = len(list1)
    n = len(list2)
    OK = 0  # 是否归结成功
    new_list = []  # 归结后的子句
    # 遍历子句中的各个公式，找到能满足归结条件的两个原子公式
    for i in range(m):
        for j in range(n):
            if list1[i].ifnot != list2[j].ifnot and list1[i].predicate == list2[j].predicate:  # 在满足归结条件的情况下
                if list1[i].parameter == list2[j].parameter:  # 不用进行合一的情况下
                    new_list = list2[:j] + list2[j + 1:] + list1[:i] + list1[i + 1:]  # 去掉两个子句的对应原子并合并
                    if if_list_in(new_list, KB) == 1:
                        OK = 1
                        addresult = ''  # 字符串形式的下一个归结步骤
                        KB.append(new_list)  # 将合并的新子句加入到子句集中
                        addresult += str(step[0]) + ' '
                        step[0] += 1
                        addresult += 'R[' + str(list1_index)  # 输出合并的原子公式1的标号
                        if m > 1:
                            addresult += str(chr(i + 97))
                        addresult += ',' + str(list2_index)  # 输出合并的原子公式2的标号
                        if n > 1:
                            addresult += str(chr(j + 97))
                        addresult += '] = '
                        addresult += list_to_str(new_list)  # 输出出加入子句集的新子句
                        result.append(addresult)  # 将新的归结步骤加入到归结步骤列表中
                        if new_list == []:  # 产生空子句则返回0，代表归结完成
                            return 0
                else:  # 需要进行合一的情况下
                    z = len(list1[i].parameter)
                    fix_list = []  # 存储合一后的子句
                    for k in range(z):
                        # 判断是否为常量（3个字母及以上为常量，其余为变量）
                        param1_is_const = len(list1[i].parameter[k]) >= 3
                        param2_is_const = len(list2[j].parameter[k]) >= 3
                        
                        # 如果一个是常量一个是变量，才进行合一
                        if param1_is_const and not param2_is_const:
                            fix_list = copy.deepcopy(list2)  # 深拷贝合一前的子句
                            # 遍历子句中的所有公式的参数，将该变量替换为常量
                            for t in range(n):
                                for r in range(len(list2[t].parameter)):
                                    if list2[t].parameter[r] == list2[j].parameter[k]:
                                        fix_list[t].parameter[r] = list1[i].parameter[k]
                            new_list = fix_list[:j] + fix_list[j + 1:] + list1[:i] + list1[i + 1:]  # 去掉两个子句的对应原子并合并
                            if if_list_in(new_list, KB) == 1:
                                OK = 1
                                addresult = ''  # 字符串形式的下一个归结步骤
                                KB.append(new_list)  # 将合并的新子句加入到子句集中
                                addresult += str(step[0]) + ' '
                                step[0] += 1
                                addresult += 'R[' + str(list1_index)  # 输出合并的原子公式1的标号
                                if m > 1:
                                    addresult += str(chr(i + 97))
                                addresult += ',' + str(list2_index)  # 输出合并的原子公式2的标号
                                if n > 1:
                                    addresult += str(chr(j + 97))
                                addresult += ']{' + str(list2[j].parameter[k]) + '=' + str(
                                    list1[i].parameter[k]) + '} = '  # 输出具体的变量和常量
                                addresult += list_to_str(new_list)  # 输出加入子句集的新子句
                                result.append(addresult)  # 将新的归结步骤加入到归结步骤列表中
                                if new_list == []:  # 产生空子句则返回0，代表归结完成
                                    return 0
                        elif param2_is_const and not param1_is_const:
                            fix_list = copy.deepcopy(list1)
                            # 遍历子句中的所有公式的参数，将该变量替换为常量
                            for t in range(m):
                                for r in range(len(list1[t].parameter)):
                                    if list1[t].parameter[r] == list1[i].parameter[k]:
                                        fix_list[t].parameter[r] = list2[j].parameter[k]
                            new_list = list2[:j] + list2[j + 1:] + fix_list[:i] + fix_list[i + 1:]  # 去掉两个子句的对应原子并合并
                            if if_list_in(new_list, KB) == 1:
                                OK = 1
                                addresult = ''  # 字符串形式的下一个归结步骤
                                KB.append(new_list)  # 将合并的新子句加入到子句集中
                                addresult += str(step[0]) + ' '
                                step[0] += 1
                                addresult += 'R[' + str(list1_index)  # 输出合并的原子公式1的标号
                                if m > 1:
                                    addresult += str(chr(i + 97))
                                addresult += ',' + str(list2_index)  # 输出合并的原子公式2的标号
                                if n > 1:
                                    addresult += str(chr(j + 97))
                                addresult += ']{' + str(list1[i].parameter[k]) + '=' + str(
                                    list2[j].parameter[k]) + '} = '  # 输出具体的变量和常量
                                addresult += list_to_str(new_list)  # 输出加入子句集的新子句
                                result.append(addresult)  # 将新的归结步骤加入到归结步骤列表中
                                if new_list == []:  # 产生空子句则返回0，代表归结完成
                                    return 0

    return 1

def str_to_fml(str):
    n = len(str)
    ifnot = 1
    predicate = ''
    parameter = []
    if str[0] == '~':
        ifnot = 0
    ifname = 0
    begin = 0
    for i in range(n):
        if str[i] == '(':
            ifname = 1
            begin = i + 1
            if ifnot == 1:
                predicate = str[0:i]
            else:
                predicate = str[1:i]
        if ifname == 1:
            if str[i] == ',' or str[i] == ')':
                parameter.append(str[begin:i])
                begin = i + 1
    new_formula = fml(ifnot, predicate, parameter)
    return new_formula

def to_list_of_class(KB):
    for i in range(len(KB)):
        for j in range(len(KB[i])):
            KB[i][j] = str_to_fml(KB[i][j])

# 子句集归结的主函数
def ResolutionFOL(KB):
    # 存储所有归结步骤
    result = []
    # 将KB从元组转换为列表，便于操作
    KB = [list(clause) for clause in KB]
    # 将字符串表示转换为公式对象
    to_list_of_class(KB)
    # 初始化步骤计数器，用于跟踪归结过程
    step = [1]  # 使用列表以便在嵌套函数中修改
    # 输出知识库中的初始子句
    for i, clause in enumerate(KB):
        new_step = f"{step[0]} {list_to_str(clause)}"
        step[0] += 1
        result.append(new_step)
    # 实现归结策略
    # 尝试所有可能的归结组合，直到推导出空子句（矛盾）
    # 或穷尽所有可能性
    # 首先，尝试每个子句与所有其他子句进行归结
    for k in range(len(KB)):
        # 对于KB中的每一对子句
        for i in range(len(KB)):
            for j in range(i + 1, len(KB)):
                # 尝试对子句i和j进行归结
                # 如果归结产生空子句（发现矛盾）
                if resolution(KB[i], KB[j], i + 1, j + 1, KB, step, result) == 0:
                    return result  # 归结成功，返回步骤
                    
    # 如果穷尽所有可能而没有找到矛盾
    return result

