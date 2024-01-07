from pulp import *

prob = LpProblem("",LpMaximize);

total_profit = 0
num_toys, num_bundles, max_toys = map(int,input().split())

profit = {}
capacity = {}
toys_bundles = {}
#for each toy (key) the value is a list with the bundles the toy is part of
variables = {}
for i in range(1,num_toys+num_bundles+1):
    if (i <= num_toys):
        profit[i], capacity[i] = map(int,input().split())
        variables[i] = (LpVariable("",0,capacity[i]+1,cat=LpInteger))
    else:
        toy1,toy2,toy3,profit[i] = map(int,input().split())
        toys_bundles.setdefault(toy1, []).append(i)
        toys_bundles.setdefault(toy2, []).append(i)
        toys_bundles.setdefault(toy3, []).append(i)
        variables[i] = LpVariable("",0,min(min(capacity[toy1],capacity[toy2]),capacity[toy3])+1,cat = LpInteger)

vars = LpVariable.dict("", variables, 0, None, LpInteger)

prob += lpSum([vars[i] * profit[i] for i in range(1,num_bundles+num_toys+1)])
prob += lpSum([vars[i] * (3 if i > num_toys else 1) for i in range(1,num_bundles+num_toys+1)]) <= max_toys,"bas"
#bundle has 3 toys

for t_b in range(1,num_toys+1):
    if t_b in toys_bundles: # at least one bundle exists with the toy
        prob += (vars[t_b] + lpSum(vars[toys_bundles[t_b][i]] for i in range(len(toys_bundles[t_b])))) <= capacity[t_b]    ,f"aasdf{t_b}"                    
    else:
        prob += (vars[t_b]) <= capacity[t_b],f"aasdf{t_b}"


prob.solve(GLPK(msg=0))
print(value(prob.objective))