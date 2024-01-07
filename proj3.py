from pulp import *

prob = LpProblem("",LpMaximize);

total_profit = 0
num_toys, num_bundles, max_toys = map(int,input().split())

toys_and_bundles = list(range(1,num_toys+num_bundles+1))
#list of toys and bundles
profit = {}
capacity = {}
toys_bundles = {}
#for each toy (key) the value is a list with the bundles the toy is part of

for i in range(1,num_toys+num_bundles+1):
    var = LpVariable("",0,None,LpInteger)
    if (i <= num_toys):
        profit[i], capacity[i] = map(int,input().split())
        
    else:
        toy1,toy2,toy3,profit[i] = map(int,input().split())
        toys_bundles.setdefault(toy1, []).append(i)
        toys_bundles.setdefault(toy2, []).append(i)
        toys_bundles.setdefault(toy3, []).append(i)


vars = LpVariable.dict("", toys_and_bundles, 0, None, LpInteger)

prob += lpSum([vars[t_b] * profit[t_b] for t_b in toys_and_bundles])

prob += lpSum(vars[t_b] * (3 if t_b > num_toys else 1) for t_b in toys_and_bundles) <= max_toys
#bundle has 3 toys

for t_b in range(1,num_toys+1):
    if t_b in toys_bundles: # at least one bundle exists with the toy
        prob += (vars[t_b] + lpSum(vars[toys_bundles[t_b][i]] for i in range(len(toys_bundles[t_b])))) <= capacity[t_b]                        
    else:
        prob += (vars[t_b]) <= capacity[t_b]

prob.solve(GLPK(msg=0))
print(value(prob.objective))