import math
import sys
f = open(sys.argv[1], "r")
particles = []
for l in f.readlines():
  l = l.split(', ')
  p = {}
  p['p'] = list(map(int, l[0][3:-1].split(',')))
  p['v'] = list(map(int, l[1][3:-1].split(',')))
  p['a'] = list(map(int, l[2][3:-2].split(',')))
  particles.append(p)

collisions = dict()
for i in range(len(particles) - 1):
  for j in range(i + 1, len(particles)):
    xpi = particles[i]['p'][0]
    xai = particles[i]['a'][0]
    xvi = particles[i]['v'][0] + 0.5*xai
    xpj = particles[j]['p'][0]
    xaj = particles[j]['a'][0]
    xvj = particles[j]['v'][0] + 0.5*xaj
    a = 0.5 * (xai - xaj)
    b = xvi - xvj
    c = xpi - xpj

    times = []
    if a == 0:
      if b != 0:
        times.append(-c/b)
    else:
      bb = b * b
      ac4 = a * c * 4
      if bb < ac4:
        continue
      elif bb == ac4:
        times.append(-b / (2 * a))
      else:
        rt = math.sqrt(bb - ac4)
        times.append((-b + rt) / (2 * a))
        times.append((-b - rt) / (2 * a))

    times = list(map(int, [t for t in times if t >= 0 and round(t) == t]))
    for t in times:
      collide = True
      for k in [1, 2]:
        pi = particles[i]['p'][k]
        ai = particles[i]['a'][k]
        vi = particles[i]['v'][k] + 0.5*ai
        pj = particles[j]['p'][k]
        aj = particles[j]['a'][k]
        vj = particles[j]['v'][k] + 0.5*aj
        a = 0.5 * (ai - aj)
        b = vi - vj
        c = pi - pj
        if a * t * t + b * t + c != 0:
          collide = False
          break
      if collide == True:
        if t not in collisions:
          collisions[t] = list()
        collisions[t].append((i, j))

p = set(range(len(particles)))

for key in sorted(list(collisions.keys())):
  r = set()
  for i, j in collisions[key]:
    if i in p and j in p:
      r.add(i)
      r.add(j)
  if r:
    print(key,*r)
  for i in r:
    p.remove(i)

print(len(p))
