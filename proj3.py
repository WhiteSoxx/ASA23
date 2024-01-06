from pulp import *

prob = LpProblem("",LpMaximize);

num_toys, num_bundles, max_toys = map(int,input().split())

toys_and_bundles = list(range(1,num_toys+num_bundles+1))
profit = {}
capacity = {}
toys_bundles = {}

for i in range(1,num_toys+num_bundles+1):
    if (i <= num_toys):
        profit[i], capacity[i] = map(int,input().split())
    else:
        toy1,toy2,toy3,profit[i] = map(int,input().split())
        toys_bundles.setdefault(toy1, []).append(i)
        toys_bundles.setdefault(toy2, []).append(i)
        toys_bundles.setdefault(toy3, []).append(i)

for i in range(0,num_bundles+num_toys):
    print(f'Index: {i}, Valor: {toys_and_bundles[i]}, Profit: {profit[i+1]}')
    if (i <= num_toys - 1):
        print(f'Capacity: {capacity[i+1]}')

for key,value in toys_bundles.items():
    print(f'Toy: {key}, Lista de bundles: {value}')


vars = LpVariable.dict("", toys_and_bundles, 0, None, LpInteger)

prob += lpSum([vars[t_b] * profit[t_b] for t_b in toys_and_bundles])

prob += lpSum(vars[t_b] * (3 if t_b > num_toys else 1) for t_b in toys_and_bundles) <= max_toys

# for t_b in toys_and_bundles:
#     if t_b in toys_bundles:
#         prob += lpSum(vars[t_b] +) <= capacity[t_b]
#     else:
#         prob += vars[t_b] <= 

#prob += lpSum()




# for i in range(num_toys):
#     print(profit[i+1], capacity[i+1])


#LP variable são as quantidades totais
    # (n[i] + p[i](se tiver o brinquedo)) dos toys 

#print(toys, packages,max_toys)

#prob.solve(GLPK(msg=0))